# Detailed Code Explanation

## 1. Big Logic

### `int main`

- **Steps**  
  1. Ensures exactly one argument.  
  2. Parses the `.cub` file into a `t_map` struct.  
  3. Initializes all rendering & game state from the map.  
  4. Performs the first rendering pass.  
  5. Displays the rendered image into the window.  
  6. Hooks keyboard presses and window-close events.  
  7. Enters the event loop (re-renders on each key event).

---

## 2. Rendering

### **File:** `render.c`

#### `void put_pixel(t_img *img, int x, int y, int color)`
- **Purpose:** Plot a single pixel of the given color into the MLX image buffer.  
- **Parameters:**  
  - `img` – pointer to off-screen image (`t_img`)  
  - `x, y` – screen coordinates (0 ≤ x < WIDTH, 0 ≤ y < HEIGHT)  
  - `color` – `0xRRGGBB` integer  
- **Description:**  
  Computes the address in `img->addr` (using `bits_per_pixel` and `line_length`) and writes the 4-byte color value.

#### `void render_scene(t_cub_data *data, t_scene *scene)`
- **Purpose:** Drive the full ray-casting “draw one frame” pass.  
- **Parameters:**  
  - `data` – top-level struct (includes player, FOV scale, textures)  
  - `scene` – contains the draw context and player reference  
- **Description:**  
  1. Sets `scene->player` from `data->player`.  
  2. Calls `draw_ceil_floor(scene)` to fill flat ceiling and floor.  
  3. Computes camera plane from player direction and FOV scale.  
  4. Loops `x` from `0` to `WINDOW_WIDTH - 1` and calls `render_column(data, scene, x)`.

---

### **File:** `render_init.c`

#### `t_texture *add_wall_pixels(t_draw *draw, char *file)`
- **Purpose:** Load a single wall texture from file into an MLX image and return its `t_texture`.  
- **Parameters:**  
  - `draw` – holds the MLX connection  
  - `file` – path to a `.xpm` wall texture  
- **Description:**  
  Uses `mlx_xpm_file_to_image`, retrieves width/height and `addr` via `mlx_get_data_addr`, wraps in `t_texture`, returns `NULL` on failure.

#### `t_scene *render_init(t_cub_data *data, t_map *map)`
- **Purpose:** Allocate and populate the `t_scene` for rendering.  
- **Parameters:**  
  - `data` – top-level game state  
  - `map` – parsed `.cub` map  
- **Description:**  
  1. Calls `init_scene_basics(data, map)`.  
  2. Calls `setup_draw_and_textures(scene, map)` (window, frame buffer, textures).  
  3. Returns the filled `t_scene` or `NULL` on error.

---

### **File:** `render_init_utils_1.c`

#### `float get_fov_scale(void)`
- **Purpose:** Compute camera plane length based on the FOV constant.  
- **Description:**  
  Converts `FOV` to radians and returns `tan(fov_rad / 2)`.

#### `int rgb_to_color(t_rgb *color)`
- **Purpose:** Pack three 0–255 values into one `0xRRGGBB` integer.  
- **Description:**  
  Shifts `r` by 16 bits, `g` by 8 bits, ORs with `b`.

---

### **File:** `render_init_utils_2.c`

#### `void set_dimensions(t_map *map, int *width, int *height)`
- **Purpose:** Determine final drawing resolution from map or defaults.  
- **Parameters:**  
  - `map` – may carry override resolution  
  - `width, height` – output pointers  

#### `int setup_draw_and_textures(t_scene *scene, t_map *map)`
- **Purpose:** Create window/frame buffer and load textures.  
- **Description:**  
  1. Calls `draw_init(map)`.  
  2. Calls `load_textures(scene->draw, map)`.  
  3. Returns `1` on success, `0` on failure.

---

### **File:** `render_ray_utils.c`

#### `void calculate_ray(t_scene *scene, int x, t_ray *ray)`
- **Purpose:** Initialize a `t_ray` for screen column `x`.  
- **Description:**  
  Computes ray direction from player dir + camera plane, sets `map_x/map_y`, calculates `delta_dist_*`, chooses `step_*` and `side_dist_*`.

#### `double calculate_wall_distance(t_scene *scene, t_ray *ray, int map_x, int map_y)`
- **Purpose:** Compute perpendicular distance to the wall after DDA hit.  
- **Description:**  
  Uses different formulas depending on `ray->side`, returns `perp_dist`.

---

### **File:** `render_tex_utils.c`

#### `unsigned int get_tex_pixel(t_texture *tex, int x, int y)`
- **Purpose:** Read a pixel’s color from a texture.  
- **Parameters:**  
  - `tex` – texture containing `img.addr`, `line_length`, etc.  
  - `x, y` – texture coordinates  
- **Description:**  
  Calculates offset `(y*line_length + x*(bpp/8))`, returns the 4-byte color.

#### `int calculate_tex_x(t_scene *scene, t_ray *ray, double perp_dist, t_texture *tex)`
- **Purpose:** Determine which vertical slice of the wall texture to sample.  
- **Description:**  
  1. Computes exact hit position `wall_x`.  
  2. Uses fractional part of `wall_x * tex->width`.  
  3. Flips `tex_x` for certain ray directions, returns `tex_x`.

---

## 3. Parsing

### **File:** `finalize_grid.c`

#### `static size_t find_maxlen(char **raw, int rows)`
- **Purpose:** Find the length of the longest string in `raw`.  
- **Parameters:**  
  - `raw` – array of `rows` strings  
  - `rows` – count of entries  
- **Description:** Returns the maximum `strlen(raw[i])`.

#### `static char **alloc_grid(int rows, int cols)`
- **Purpose:** Allocate a rectangular `rows × cols` grid.  
- **Parameters:**  
  - `rows`, `cols` – dimensions  
- **Description:** Allocates `rows` pointers, each with `cols+1` bytes.

#### `static void fill_grid(char **grid, char **raw, int rows, int cols)`
- **Purpose:** Copy `raw` into `grid`, padding with spaces.  
- **Parameters:**  
  - `grid`, `raw`, `rows`, `cols`  
- **Description:** Copies each line, fills remainder with `' '`, null-terminates.

#### `static void free_raw(char **raw, int rows)`
- **Purpose:** Free the ragged `raw` array.  
- **Parameters:**  
  - `raw`, `rows`  
- **Description:** Frees `raw[i]` then `raw`.

#### `char **finalize_grid(char **raw, int rows, int *out_cols)`
- **Purpose:** Convert ragged `raw` into a rectangular grid.  
- **Parameters:**  
  - `raw`, `rows`, `out_cols`  
- **Description:**  
  1. Compute `*out_cols` via `find_maxlen`.  
  2. Allocate via `alloc_grid`.  
  3. Fill with `fill_grid`.  
  4. Free `raw` with `free_raw`.  
  5. Return new `grid`.

---

### **File:** `parsing_utils_1.c`

#### `void parse_color_line(char **target, char *line)`
- **Purpose:** Capture a floor/ceiling color directive.  
- **Parameters:**  
  - `target` – address of `map->floor` or `map->ceil`  
  - `line` – stripped `"F …"` or `"C …"`  
- **Description:** Duplicates `line+1` into `*target`.

#### `void add_map_line(t_map *map, char *line, char ***grid, int *rows)`
- **Purpose:** Append one map row to the raw grid.  
- **Parameters:**  
  - `map`, `line`, `grid`, `rows`  
- **Description:** Uses `realloc_list` to grow `grid`, duplicates `line`, increments `*rows`.

#### `void process_line(t_map *map, char *line, char ***grid, int *rows)`
- **Purpose:** Dispatch a stripped line to the correct parser.  
- **Parameters:**  
  - `map`, `line`, `grid`, `rows`  
- **Description:** Calls `parse_resolution_line`, `parse_texture_line`, `parse_color_line`, or `add_map_line`, or errors.

#### `void read_map_lines(int fd, t_map *map)`
- **Purpose:** Read & process all lines from the map file.  
- **Parameters:**  
  - `fd`, `map`  
- **Description:** Loops `get_next_line`, strips, skips blanks, calls `process_line`, stores `map->map` and `map->rows`.

---

### **File:** `parsing_utils_2.c`

#### `t_map *init_map_struct(void)`
- **Purpose:** Allocate and zero a new `t_map`.  
- **Returns:** Pointer to new `t_map`, or exits on failure.

#### `bool is_texture_line(char *line)`
- **Purpose:** Identify `NO `, `SO `, `WE `, `EA ` directives.  
- **Returns:** `true` if matches one of the four.

#### `bool is_map_line(char *line)`
- **Purpose:** Detect start of the map grid (`'1'` first).  
- **Returns:** `true` if first non-space is `'1'`.

#### `bool is_blank_line(char *line)`
- **Purpose:** Detect lines of only whitespace.  
- **Returns:** `true` if `line` is `NULL` or all spaces/tabs.

#### `char *strip_line(const char *line)`
- **Purpose:** Duplicate a line without trailing `\n`.  
- **Returns:** Allocated copy or `NULL`.

---

### **File:** `parsing_utils_3.c`

#### `void parse_resolution_line(t_map *map, char *line)`
- **Purpose:** Parse `R width height`.  
- **Parameters:** `map`, `line`  
- **Description:** Splits `line+1`, converts tokens to `map->res_w`/`res_h`, validates.

#### `void parse_texture_line(t_map *map, char *line)`
- **Purpose:** Parse `NO `, `SO `, `WE `, `EA ` paths.  
- **Parameters:** `map`, `line`  
- **Description:** Duplicates `line+3` into the appropriate `map->file_*` field.

---

### **File:** `validate_map.c`

#### `static int count_player_starts_in_row(char *row, int max_cols)`
- **Purpose:** Count `N`, `S`, `E`, `W` in one row.  
- **Returns:** Number of start markers.

#### `static int count_player_starts(t_map *map)`
- **Purpose:** Sum all start markers in the grid.  
- **Returns:** Total count.

#### `static void check_cell_enclosed(t_map *map, int y, int x)`
- **Purpose:** Ensure a walkable cell is not on the border or next to a space.  
- **Description:** Errors if enclosure is violated.

#### `static void check_map_enclosure(t_map *map)`
- **Purpose:** Validate all walkable/start cells are enclosed by walls.

#### `void validate_map(t_map *map)`
- **Purpose:** Top-level map integrity check.  
- **Description:** Verifies non-NULL, exactly one player start, calls `check_map_enclosure`.

---

## 4. Player Initialization

### File: `player_init.c`

#### `char find_player_position(t_map *map, int *x_pos, int *y_pos)`
- **Purpose:** Locate the player’s start cell and orientation in the parsed map.  
- **Parameters:**  
  - `map`   – pointer to the `t_map` containing `map->grid`.  
  - `x_pos` – output pointer for the player’s column index.  
  - `y_pos` – output pointer for the player’s row index.  
- **Description:**  
  Scans every cell of `map->grid`; on encountering one of `'N'`, `'S'`, `'E'`, or `'W'`, it:
  1. Records the character (orientation) as the return value.  
  2. Stores its coordinates in `*x_pos` and `*y_pos`.  
  3. Replaces that cell with `'0'` (empty space).  
  4. Continues or returns early once exactly one start is found; errors if zero or multiple starts.

#### `void rotate_player(t_player *player, double angle)`
- **Purpose:** Rotate the player’s view direction and camera plane by a given angle.  
- **Parameters:**  
  - `player` – pointer to the `t_player` to modify.  
  - `angle`  – rotation angle in radians (positive = turn right, negative = turn left).  
- **Description:**  
  1. Saves `old_dir_x` and `old_plane_x`.  
  2. Updates `player->d_x` and `player->d_y` by applying the 2D rotation matrix.  
  3. Updates `player->plane_x` and `player->plane_y` similarly, preserving the perpendicular camera plane for proper perspective.

---

## 5. Player Movement

### File: `player_movement.c`

#### `void move_forward_backward(t_cub_data *data, t_player *player, double speed)`
- **Purpose:** Move the player forward or backward, with collision checks.  
- **Parameters:**  
  - `data`   – top-level `t_cub_data`, used to access the map (`data->scene->map->grid`).  
  - `player` – the `t_player` whose position to update.  
  - `speed`  – move increment (positive for forward, negative for backward).  
- **Description:**  
  1. Computes tentative new `x = player->pos_x + player->d_x * speed`.  
  2. If `grid[int(new_y)][int(player->pos_x)]` is not a wall (`'1'`), updates `player->pos_y`.  
  3. Computes tentative new `y = player->pos_y + player->d_y * speed`.  
  4. If `grid[int(player->pos_y)][int(new_x)]` is not a wall, updates `player->pos_x`.  
  This two-step approach prevents getting “stuck” on diagonal movements and enforces basic collision.

#### `void rotate_player(t_player *player, double angle)`
- **Purpose & Description:** Same as in `player_init.c`—rotates the player’s direction vector and camera plane by `angle`.  
- **Note:** Defined here again for reuse in input handling; identical implementation.

---

## 6. Exit & Cleanup

### File: `exit_game_helpers.c`

#### `void exit_game(t_cub_data *data)`  
- **Purpose:** Cleanly exit the application, freeing all resources.  
- **Parameters:**  
  - `data` – top-level struct holding all game state, textures, images, and map data.  
- **Description:**  
  1. Calls `free_all_data(data)` to release textures, images, the map grid, the scene, and the MLX window.  
  2. Calls `exit(EXIT_SUCCESS)`.

#### `void close_window(t_cub_data *data)`  
- **Purpose:** MLX callback for the window-close (red X) event.  
- **Parameters:**  
  - `data` – same top-level struct passed to all callbacks.  
- **Description:**  
  Invokes `exit_game(data)`.

#### `void free_all_data(t_cub_data *data)`  
- **Purpose:** Release every allocated resource before quitting.  
- **Parameters:**  
  - `data` – top-level struct.  
- **Description:**  
  1. Destroys the MLX image buffer via `mlx_destroy_image`.  
  2. Destroys the MLX window via `mlx_destroy_window`.  
  3. Frees each texture image.  
  4. Frees the map grid with `ft_free_split`.  
  5. Frees the `t_scene` and finally the `t_cub_data` struct itself.

---

## 7. Input Handling

### File: `key_handler.c`

#### `int key_press(int keycode, t_cub_data *data)`  
- **Purpose:** Central dispatch for all key-press events.  
- **Parameters:**  
  - `keycode` – X11 keysym code of the pressed key.  
  - `data`    – top-level struct with scene, player, and MLX context.  
- **Description:**  
  1. If `keycode == ESC`, calls `exit_game(data)`.  
  2. If `KEY_W` or `KEY_S`, calls `move_forward_backward(data, player, ±MOVE_SPEED)`.  
  3. If `KEY_A` or `KEY_D`, calls `strafe_left_right(data, player, ±MOVE_SPEED)`.  
  4. If `LEFT_ARROW` or `RIGHT_ARROW`, calls `rotate_player(player, ±ROT_SPEED)`.  
  5. After any movement or rotation, re‐renders the scene with `render_scene(data, scene)` and updates the window.

---

### File: `key_press_helpers.c`

#### `void handle_movement_keys(int keycode, t_cub_data *data)`  
- **Purpose:** Isolate W/A/S/D movement logic from the main key handler.  
- **Parameters:**  
  - `keycode` – which movement key was pressed.  
  - `data`    – top-level struct.  
- **Description:**  
  - `KEY_W` → `move_forward_backward(data, player,  MOVE_SPEED)

---
