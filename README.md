### Documentation of the Logic of the Project(cub3D).

This document is written with the purpose of explaining the all in all logic of the project and also the detailed explanation of each function of every part.

# cub3D

A MiniLibX‑based ray‑casting engine in C, inspired by Wolfenstein 3D.

![Ray‑casting Diagram](files/subject_description/raycasting_diagram.png)

---

## Big‑Picture Logic

**cub3D** implements the classic ray‑casting algorithm to transform a 2D grid map into a real‑time, first‑person 3D view. For **each** vertical column of pixels:

1. **Cast a Ray**
   From the player’s position at a specific angle within the field of view.
2. **Step Through the Grid**
   Use DDA (Digital Differential Analyzer) to advance cell by cell along the ray until you hit a wall.
3. **Compute Distance**
   Measure how far the ray traveled to the wall—this determines the wall slice height.
4. **Project & Texture**
   Calculate on‑screen line height (`height = window_height / distance`), select the correct wall texture (based on side hit), and sample the texture column.
5. **Draw Floor & Ceiling**
   Fill pixels above the wall slice with the ceiling color and below with the floor color.

---

## Project Objective

Produce a **robust**, **memory‑safe**, **MiniLibX**‑based ray‑caster that:

* Parses a single `.cub` configuration file for:

  * **North/South/East/West** wall textures
  * Floor and ceiling RGB colors
  * A closed rectangular map with exactly one player start (N/S/E/W)
* Renders a real‑time 3D first‑person view with:

  * Wall textures
  * Flat floor & ceiling colors
* Supports:

  * **Movement:** W/A/S/D with collision checks
  * **Looking:** ←/→ arrow keys
  * **Exit:** ESC key or window close
* Validates input strictly and reports clear error messages for malformed files or maps

---

## File Overview

* **`cub3D.pdf`**
  Project specification and mandatory requirements.

* **`main.c`**

  * Entry point: argument validation
  * Map parsing via `parse_map()`
  * Initialization via `data_init()`
  * Initial render via `render_scene()`
  * Event hooks for keyboard and window events
  * `mlx_loop` for continuous updates

* **`helper_tools.c`**
  Utility functions:

  * `exit_error(msg)` — print error & exit
  * `ft_free_split(arr)` — free string arrays
  * `realloc_list(list, n)` — resize arrays of strings
  * `cleanup_partial_data(data)` — free partial state on error

* **Header Files**

  * `defines.h` — constants (window size, FOV, π, keycodes)
  * `functions.h` — function prototypes
  * `structs.h` — data structures for map, player, ray, drawing, scene

---

## Detailed Code Explanation

### `main.c`

```c
#include "../inc/functions.h"
```

Imports all prototypes, constants, and data structures.

```c
int main(int argc, char **argv)
{
    t_map      *map;
    t_cub_data *data;

    if (argc != 2)
        exit_error("Usage: ./cub3D <map.cub>");
```

* **Argument check:** ensures exactly one `.cub` file is provided.

```c
    map = parse_map(argv[1]);
```

* **Map Parsing:** loads textures, floor/ceiling colors, and validates the map grid (closed walls).

```c
    data = data_init(map);
```

* **Initialization:** sets player position/orientation, computes camera plane, initializes MiniLibX window & image.

```c
    render_scene(data, data->scene);
    mlx_put_image_to_window(
        data->scene->draw->mlx_conn,
        data->scene->draw->win,
        data->scene->draw->img,
        0, 0
    );
```

* **Rendering:** ray‑casting loop over screen columns, distance calculation, texture sampling, and floor/ceiling fill; then display image.

```c
    mlx_hook(
        data->scene->draw->win,
        KeyPress,
        KeyPressMask,
        key_press,
        data
    );

    mlx_hook(
        data->scene->draw->win,
        33,         // DestroyNotify
        1L<<17,
        close_window,
        data
    );

    mlx_loop(data->scene->draw->mlx_conn);
    return 0;
}
```

* **Event Loop:** handles movement/rotation, window close, then enters MLX loop.

---

### `helper_tools.c`

```c
void exit_error(char *msg)
{
    // Print "Error\n" + msg to stderr and exit(1).
}
```

Unified error reporting and exit.

```c
void ft_free_split(char **arr)
{
    // Free each string in arr and then the array itself.
}
```

Frees a NULL‑terminated string array.

```c
char **realloc_list(char **list, int new_count)
{
    char **new_list = malloc(sizeof(char *) * (new_count + 1));
    if (!new_list)
        exit_error("Memory allocation failed in realloc_list");
    // Copy pointers, null‑terminate, free old list.
    return new_list;
}
```

Safely resizes an array of strings.

```c
void cleanup_partial_data(t_cub_data *data)
{
    if (data->player)
        free(data->player);
    free(data);
}
```

Cleanup on partial failure.

---

### Header Files

* **`defines.h`** — window size, FOV, π, keycodes
* **`functions.h`** — parsing, validation, init, render, helpers
* **`structs.h`** — `t_map`, `t_player`, `t_ray`, `t_draw`, `t_scene`, `t_cub_data`

---

### Rendering

## `put_pixel` Function

```c
void put_pixel(t_img *img, int x, int y, int color)
{
    // Writes `color` into the image buffer at coordinates (x,y).
    char *dst;

    // Compute byte offset: y * line_length + x * (bpp/8)
    dst = img->pixels + (y * img->line_length + x * (img->bpp / 8));
    *(unsigned int*)dst = color;
}
```

* **Purpose:** Low-level pixel writer for the MLX image buffer.
* **Parameters:**

  * `img`: pointer to a `t_img` struct with fields `pixels`, `line_length`, and `bpp`.
  * `x, y`: screen coordinates.
  * `color`: 32-bit integer representing ARGB/RGB color.
* **Operation:** Calculates the correct byte offset into `img->pixels` and writes the `unsigned int` color value.

---

## `draw_ceil_floor` Function

```c
void draw_ceil_floor(t_scene *scene)
{
    int x;
    int y;

    y = 0;
    while (y < WINDOW_HEIGHT)
    {
        x = 0;
        while (x < WINDOW_WIDTH)
        {
            if (y < WINDOW_HEIGHT / 2)
                put_pixel(scene->draw->img, x, y, scene->ceil_color);
            else
                put_pixel(scene->draw->img, x, y, scene->floor_color);
            x++;
        }
        y++;
    }
}
```

* **Purpose:** Fill the entire screen background with two flat colors: ceiling on the top half, floor on the bottom half.
* **Logic:** Nested loops over `y` (rows) and `x` (columns):

  * If row is above midpoint, use `scene->ceil_color`.
  * Otherwise, use `scene->floor_color`.
* **Effect:** Prepares a clear background before drawing walls.

---

## `render_scene` Function

```c
void render_scene(t_cub_data *data, t_scene *scene)
{
    int x;

    // Link scene back to the current player state
    scene->player = data->player;

    // Draw flat ceiling and floor
    draw_ceil_floor(scene);

    // Compute camera plane from player direction and FOV
    scene->plane_x = -(scene->player->d_y) * scene->fov_scale;
    scene->plane_y =  (scene->player->d_x) * scene->fov_scale;

    // Cast one ray per vertical stripe
    x = 0;
    while (x < WINDOW_WIDTH)
    {
        render_column(data, scene, x);
        x++;
    }
}
```

* **Purpose:** Main per-frame routine. Clears background, sets up camera plane, then casts rays column by column.
* **Steps:**

  1. **Attach Player:** Sync `scene->player` pointer to `data->player`.
  2. **Background:** Call `draw_ceil_floor()`.
  3. **Camera Plane:** Calculate 2D plane vector from player direction (`d_x`, `d_y`) and precomputed `fov_scale`.
  4. **Ray Loop:** For each screen column `x` from `0` to `WINDOW_WIDTH - 1`, call `render_column()`.
* **Note:** `render_column` performs ray direction, DDA stepping, distance calculation, projection, and texturing (defined elsewhere).

---

# Detailed Code Explanation

A concise, GitHub-style overview focusing solely on explanations for each rendering module source file.

---

## `render_init_utils_1.c`

* **get\_fov\_scale**: Converts the field-of-view angle (`FOV`) from degrees to a scale factor for the camera plane by converting to radians and taking the tangent of half the angle.
* **rgb\_to\_color**: Packs individual red, green, and blue components into a single 24-bit integer for efficient color storage.

---

## `render_init_utils_2.c`

* **set\_dimensions**: Determines the rendering window’s width and height, prioritizing values from the map configuration if specified, otherwise falling back to predefined defaults.
* **init\_image**: Allocates and initializes an MLX image buffer, retrieving metadata such as bits-per-pixel, line length, and endian format.
* **setup\_draw\_and\_textures**: Initializes the drawing context and loads wall textures; performs cleanup on failure.

---

## `render_init.c`

* **add\_wall\_pixels**: Loads a single wall texture from an XPM file into memory, storing its dimensions and pixel buffer for later sampling.
* **load\_textures**: Aggregates loading of all four cardinal wall textures, handling errors by freeing partially loaded resources.
* **render\_init**: Composes the overall scene initialization, tying together basic scene setup with drawing context and texture loading.

---

## `render_ray_utils.c`

* **calculate\_ray**: Calculates the ray’s direction vector and distance increments (`delta_dist`) based on the camera plane and the current screen column.
* **init\_ray\_steps**: Determines the ray’s starting map cell, step directions, and initial side distances for Digital Differential Analyzer (DDA) traversal.
* **perform\_dda**: Advances the ray cell by cell until it intersects a wall, setting a flag when a hit occurs and tracking whether the collision was vertical or horizontal.

---

## `render_tex_utils.c`

* **get\_tex\_pixel**: Retrieves the color value from a texture’s pixel buffer at specified coordinates.
* **calculate\_projection**: Computes the projected wall slice height and vertical drawing boundaries to correctly position it on screen.
* **choose\_texture**: Selects the appropriate wall texture based on which side (X or Y) the ray intersected and its direction.
* **calculate\_tex\_x**: Determines the horizontal texture coordinate corresponding to the wall intersection point, applying flips as needed for correct orientation.

---



---
