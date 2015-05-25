<> The final test.
<> A zooming mandlebrot fractal.

<> Complex number type.
type complex
  float real
  float imag
fin

<> 2-tuple type.
type 2tup
  float x
  float y
fin

<> prints n blank lines to the terminal.
none clear_screen(int n)
  int i
  i = 0
  while i < n
    say ""
    i = i + 1
  fin
fin

<> This is how we "sleep".
none waste_time(int amount)
  int i
  i = 0
  while i < amount
    i = i + 1
  fin
fin

<> Absolute value of complex number.
float complex_norm(float real, float imag)
  return (real ** 2.0 + imag ** 2.0) ** 0.5
fin

<> Refactored from a previous test to include complex types.
int draw_mandelbrot(float dim_x, float dim_y, float offset_x, float offset_y, float zoom, int max_iters, string symbol, bool draw)
  int iters
  int symbol_count

  float row
  float col
  float tmp

  complex c
  complex z

  while row < dim_y
    while col < dim_x
      iters = 0
      c.real = 1.5 * (col - dim_x * 0.5) / (0.5 * dim_x * zoom) + offset_x
      c.imag = 1.0 * (row - dim_y * 0.5) / (0.5 * dim_y * zoom) + offset_y
      z.real = 0.0
      z.imag = 0.0

      <> Determine convergence through repeated iteration of complex quadratic
      <>   polynomial.
      while complex_norm(z.real, z.imag) < 2.0 and iters < max_iters
        tmp = z.real ** 2.0 - z.imag ** 2.0 + c.real
        z.imag = (2.0 * z.imag * z.real) + c.imag
        z.real = tmp
        iters = iters + 1
      fin

      if iters == max_iters
        symbol_count = symbol_count + 1
        if draw
          write symbol
        fin
      fin

      if iters != max_iters and draw
        write " "
      fin

      col = col + 1.0
    fin

    if draw
      say " "
    fin

    col = 0.0
    row = row + 1.0
  fin

  return symbol_count
fin

<> Iteration limit (how many times it zooms in before stopping).
int lim
lim = 140

<> Convergence test precision.
int precision
precision = 50

<> Starting zoom.
float zoom
zoom = 1.0

<> Zoom factor to multiply by on each iteration.
float dz
dz = 1.1

<> Character to draw the fractal with.
string symbol
symbol = "*"

<> Character dimension for drawing.
2tup dim
dim.x = 80.0
dim.y = 30.0

<> Centered position of fractal.
2tup coords
coords.x = 0.0134538705
coords.y = 0.6596045187

<> Draw loop.
int j
int total_drawn

bool draw
int testing

<> Flag for testing.
write "Wanna see something cool? 0=yes, 1=no: "
testing = inp_int

if testing == 1
  lim = 10
  draw = false
fin

if testing != 1
  draw = true
fin

while j < lim
  total_drawn = draw_mandelbrot(dim.x, dim.y, coords.x, -coords.y, zoom, precision, symbol, draw) + total_drawn

  if not testing and j != lim - 1
    waste_time(5000000)
    clear_screen(80)
  fin

  zoom = zoom * dz
  j = j + 1
fin

write "Total characters produced: "
say total_drawn
