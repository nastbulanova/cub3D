# Explicação Detalhada do Código

## 1. Lógica Geral

### `int main`

- **Passos**  
  1. Garante que exatamente um argumento foi passado.  
  2. Faz o parsing do arquivo `.cub` para uma estrutura `t_map`.  
  3. Inicializa todo o estado de jogo e renderização baseado no mapa.  
  4. Executa a primeira passagem de renderização.  
  5. Exibe a imagem renderizada na janela.  
  6. Registra os eventos de teclado e fechamento de janela.  
  7. Entra no loop de eventos (re-renderiza a cada evento de teclado).

---

## 2. Renderização

### Arquivo: `render.c`

#### `void put_pixel(t_img *img, int x, int y, int color)`
- **Objetivo:** Desenhar um único pixel da cor especificada no buffer de imagem MLX.  
- **Parâmetros:**  
  - `img` – ponteiro para a imagem off-screen (`t_img`)  
  - `x, y` – coordenadas na tela (0 ≤ x < LARGURA, 0 ≤ y < ALTURA)  
  - `color` – inteiro `0xRRGGBB`  
- **Descrição:**  
  Calcula o endereço em `img->addr` (usando `bits_per_pixel` e `line_length`) e grava o valor de cor de 4 bytes.

#### `void render_scene(t_cub_data *data, t_scene *scene)`
- **Objetivo:** Conduzir toda a passagem de ray-casting para desenhar um frame.  
- **Parâmetros:**  
  - `data` – estrutura de nível superior (inclui jogador, escala FOV, texturas)  
  - `scene` – contém o contexto de desenho e referência ao jogador  
- **Descrição:**  
  1. Define `scene->player` a partir de `data->player`.  
  2. Chama `draw_ceil_floor(scene)` para preencher teto e chão.  
  3. Calcula a câmera (camera plane) a partir da direção do jogador e escala FOV.  
  4. Faz loop de `x` de 0 a `WINDOW_WIDTH - 1` e chama `render_column(data, scene, x)`.

---

### Arquivo: `render_init.c`

#### `t_texture *add_wall_pixels(t_draw *draw, char *file)`
- **Objetivo:** Carregar uma textura de parede de um arquivo para uma imagem MLX e retornar um `t_texture`.  
- **Parâmetros:**  
  - `draw` – contém a conexão MLX  
  - `file` – caminho para um arquivo `.xpm` de textura  
- **Descrição:**  
  Usa `mlx_xpm_file_to_image`, obtém largura/altura e `addr` via `mlx_get_data_addr`, envolve em `t_texture`, retorna `NULL` em falha.

#### `t_scene *render_init(t_cub_data *data, t_map *map)`
- **Objetivo:** Alocar e preencher o `t_scene` para renderização.  
- **Parâmetros:**  
  - `data` – estado de jogo de nível superior  
  - `map` – mapa `.cub` já parseado  
- **Descrição:**  
  1. Chama `init_scene_basics(data, map)`.  
  2. Chama `setup_draw_and_textures(scene, map)` (janela, buffer, texturas).  
  3. Retorna o `t_scene` preenchido ou `NULL` em caso de erro.

---

### Arquivo: `render_init_utils_1.c`

#### `float get_fov_scale(void)`
- **Objetivo:** Calcular o tamanho do plano da câmera com base na constante FOV.  
- **Descrição:**  
  Converte `FOV` em radianos e retorna `tan(fov_rad / 2)`.

#### `int rgb_to_color(t_rgb *color)`
- **Objetivo:** Empacotar três valores de 0–255 em um inteiro `0xRRGGBB`.  
- **Descrição:**  
  Desloca `r` em 16 bits, `g` em 8 bits e faz OR com `b`.

---

### Arquivo: `render_init_utils_2.c`

#### `void set_dimensions(t_map *map, int *width, int *height)`
- **Objetivo:** Determinar a resolução final de renderização a partir do mapa ou usar padrões.  
- **Parâmetros:**  
  - `map` – pode conter resolução customizada  
  - `width, height` – ponteiros de saída  

#### `int setup_draw_and_textures(t_scene *scene, t_map *map)`
- **Objetivo:** Criar janela/buffer e carregar texturas.  
- **Descrição:**  
  1. Chama `draw_init(map)`.  
  2. Chama `load_textures(scene->draw, map)`.  
  3. Retorna `1` em sucesso ou `0` em falha.

---

### Arquivo: `render_ray_utils.c`

#### `void calculate_ray(t_scene *scene, int x, t_ray *ray)`
- **Objetivo:** Inicializar um `t_ray` para a coluna de tela `x`.  
- **Descrição:**  
  Calcula direção do raio a partir de `player.dir` + `camera_plane`, define `map_x/map_y`, calcula `delta_dist_*`, escolhe `step_*` e `side_dist_*`.

#### `double calculate_wall_distance(t_scene *scene, t_ray *ray, int map_x, int map_y)`
- **Objetivo:** Calcular a distância perpendicular até a parede após o DDA.  
- **Descrição:**  
  Aplica fórmula diferente dependendo de `ray->side` e retorna `perp_dist`.

---

### Arquivo: `render_tex_utils.c`

#### `unsigned int get_tex_pixel(t_texture *tex, int x, int y)`
- **Objetivo:** Ler a cor de um pixel em uma textura.  
- **Parâmetros:**  
  - `tex` – textura com `img.addr`, `line_length`, etc.  
  - `x, y` – coordenadas na textura  
- **Descrição:**  
  Calcula offset `(y*line_length + x*(bpp/8))` e retorna o valor de 4 bytes.

#### `int calculate_tex_x(t_scene *scene, t_ray *ray, double perp_dist, t_texture *tex)`
- **Objetivo:** Determinar qual fatia vertical da textura usar.  
- **Descrição:**  
  1. Calcula posição exata de impacto `wall_x`.  
  2. Usa parte fracionária de `wall_x * tex->width`.  
  3. Inverte `tex_x` se necessário e retorna `tex_x`.

---

## 3. Parsing

### Arquivo: `finalize_grid.c`

#### `static size_t find_maxlen(char **raw, int rows)`
- **Objetivo:** Encontrar o comprimento da string mais longa em `raw`.  
- **Parâmetros:**  
  - `raw` – array de `rows` strings  
  - `rows` – número de linhas  
- **Descrição:** Retorna o maior `strlen(raw[i])`.

#### `static char **alloc_grid(int rows, int cols)`
- **Objetivo:** Alocar um grid retangular `rows × cols`.  
- **Parâmetros:**  
  - `rows`, `cols` – dimensões  
- **Descrição:** Aloca `rows` ponteiros, cada um com `cols+1` bytes.

#### `static void fill_grid(char **grid, char **raw, int rows, int cols)`
- **Objetivo:** Copiar `raw` para `grid`, preenchendo com espaços.  
- **Parâmetros:**  
  - `grid, raw, rows, cols`  
- **Descrição:** Copia cada linha, preenche o restante com `' '` e adiciona `\0`.

#### `static void free_raw(char **raw, int rows)`
- **Objetivo:** Liberar o array irregular `raw`.  
- **Parâmetros:**  
  - `raw, rows`  
- **Descrição:** Libera `raw[i]` e em seguida `raw`.

#### `char **finalize_grid(char **raw, int rows, int *out_cols)`
- **Objetivo:** Converter `raw` irregular para um grid retangular.  
- **Parâmetros:**  
  - `raw, rows, out_cols`  
- **Descrição:**  
  1. Calcula `*out_cols` com `find_maxlen`.  
  2. Aloca com `alloc_grid`.  
  3. Preenche com `fill_grid`.  
  4. Libera `raw` com `free_raw`.  
  5. Retorna o novo `grid`.

---

### Arquivo: `parsing_utils_1.c`

#### `void parse_color_line(char **target, char *line)`
- **Objetivo:** Processar diretiva de cor de piso/teto.  
- **Parâmetros:**  
  - `target` – endereço de `map->floor` ou `map->ceil`  
  - `line` – string `"F …"` ou `"C …"`  
- **Descrição:** Duplica `line+1` em `*target`.

#### `void add_map_line(t_map *map, char *line, char ***grid, int *rows)`
- **Objetivo:** Adicionar uma linha do mapa ao array bruto.  
- **Parâmetros:**  
  - `map, line, grid, rows`  
- **Descrição:** Usa `realloc_list` para crescer `grid`, duplica `line`, incrementa `*rows`.

#### `void process_line(t_map *map, char *line, char ***grid, int *rows)`
- **Objetivo:** Redirecionar a linha ao parser correto.  
- **Parâmetros:**  
  - `map, line, grid, rows`  
- **Descrição:** Chama `parse_resolution_line`, `parse_texture_line`, `parse_color_line` ou `add_map_line`; erro caso contrário.

#### `void read_map_lines(int fd, t_map *map)`
- **Objetivo:** Ler e processar todas as linhas do arquivo de mapa.  
- **Parâmetros:**  
  - `fd, map`  
- **Descrição:** Loop em `get_next_line`, limpa string, pula vazias, chama `process_line`, armazena `map->map` e `map->rows`.

---

### Arquivo: `parsing_utils_2.c`

#### `t_map *init_map_struct(void)`
- **Objetivo:** Alocar e zerar uma nova `t_map`.  
- **Retorno:** Ponteiro ou encerra em caso de erro.

#### `bool is_texture_line(char *line)`
- **Objetivo:** Identificar diretivas `NO `, `SO `, `WE `, `EA `.  
- **Retorno:** `true` se corresponder a uma delas.

#### `bool is_map_line(char *line)`
- **Objetivo:** Detectar início do bloco do mapa (`'1'`).  
- **Retorno:** `true` se o primeiro caractere não espaço for `'1'`.

#### `bool is_blank_line(char *line)`
- **Objetivo:** Detectar linha em branco.  
- **Retorno:** `true` se `line` for `NULL` ou só espaços/tabs.

#### `char *strip_line(const char *line)`
- **Objetivo:** Duplicar linha sem o `\n` final.  
- **Retorno:** Cópia alocada ou `NULL`.

---

### Arquivo: `parsing_utils_3.c`

#### `void parse_resolution_line(t_map *map, char *line)`
- **Objetivo:** Parsear `R largura altura`.  
- **Parâmetros:** `map, line`  
- **Descrição:** Divide `line+1`, converte para `map->res_w`/`map->res_h` e valida.

#### `void parse_texture_line(t_map *map, char *line)`
- **Objetivo:** Parsear caminhos `NO `, `SO `, `WE `, `EA `.  
- **Parâmetros:** `map, line`  
- **Descrição:** Duplica `line+3` no campo `map->file_*` correspondente.

---

### Arquivo: `validate_map.c`

#### `static int count_player_starts_in_row(char *row, int max_cols)`
- **Objetivo:** Contar `N`, `S`, `E`, `W` em uma linha.  

#### `static int count_player_starts(t_map *map)`
- **Objetivo:** Somar marcadores de início no grid.  

#### `static void check_cell_enclosed(t_map *map, int y, int x)`
- **Objetivo:** Garantir que célula andável esteja cercada por paredes.  

#### `static void check_map_enclosure(t_map *map)`
- **Objetivo:** Validar que todas as células andáveis/começo estejam cercadas.  

#### `void validate_map(t_map *map)`
- **Objetivo:** Validação geral do mapa.  
- **Descrição:** Verifica nulidade, único ponto de início e chama `check_map_enclosure`.

---

## 4. Inicialização do Jogador

### Arquivo: `player_init.c`

#### `char find_player_position(t_map *map, int *x_pos, int *y_pos)`
- **Objetivo:** Localizar célula inicial e orientação do jogador no mapa.  
- **Parâmetros:**  
  - `map` – ponteiro para `t_map` com `map->grid`  
  - `x_pos, y_pos` – ponteiros de saída para coordenadas  
- **Descrição:**  
  Percorre todo `map->grid`; ao encontrar `'N'`,`'S'`,`'E'` ou `'W'`:
  1. Retorna o caractere como orientação.  
  2. Armazena coordenadas em `*x_pos`/`*y_pos`.  
  3. Substitui por `'0'`.  
  4. Erra se não houver ou houver múltiplos.

#### `void rotate_player(t_player *player, double angle)`
- **Objetivo:** Rotacionar direção e plano de câmera do jogador.  
- **Parâmetros:**  
  - `player` – ponteiro para `t_player`  
  - `angle` – ângulo em radianos (positivo = direita, negativo = esquerda)  
- **Descrição:**  
  Usa matriz de rotação 2D para atualizar `dir_x/dir_y` e `plane_x/plane_y`.

---

## 5. Movimentação do Jogador

### Arquivo: `player_movement.c`

#### `void move_forward_backward(t_cub_data *data, t_player *player, double speed)`
- **Objetivo:** Mover jogador para frente/trás com colisão.  
- **Parâmetros:**  
  - `data` – `t_cub_data` com `map->grid`  
  - `player` – `t_player` a atualizar  
  - `speed` – incremento (positivo/frente, negativo/trás)  
- **Descrição:**  
  1. Tenta novo `x = pos_x + dir_x * speed` e atualiza `pos_x` se não colidir.  
  2. Tenta novo `y = pos_y + dir_y * speed` e atualiza `pos_y` se não colidir.

#### `void rotate_player(t_player *player, double angle)`
- **Objetivo/Descrição:** Mesma função de rotação anterior.

---

## 6. Saída & Limpeza

### Arquivo: `exit_game_helpers.c`

#### `void exit_game(t_cub_data *data)`
- **Objetivo:** Sair limpando todos os recursos.  
- **Parâmetros:** `data` – struct principal  
- **Descrição:**  
  1. Chama `free_all_data(data)`.  
  2. Chama `exit(EXIT_SUCCESS)`.

#### `void close_window(t_cub_data *data)`
- **Objetivo:** Callback de fechamento de janela.  
- **Parâmetros:** `data`  
- **Descrição:** Chama `exit_game(data)`.

#### `void free_all_data(t_cub_data *data)`
- **Objetivo:** Liberar todos os recursos.  
- **Descrição:**

