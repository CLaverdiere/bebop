<> This hard test draws a Mandelbrot set in ASCII art.
<> References:
<> http://jonisalonen.com/2013/lets-draw-the-mandelbrot-set/
<> https://raw.githubusercontent.com/CLaverdiere/Fractals/master/mandlebrot_fractal.py

float complex_norm(float real, float imag)
  return (real ** 2.0 + imag ** 2.0) ** 0.5
fin

int draw_mandelbrot(float dim_x, float dim_y, int max_iters)
  int iters

  float row
  float col
  float c_real
  float c_imag
  float z_real
  float z_imag
  float z_tmp

  while row < dim_y
    while col < dim_x
      iters = 0
      c_real = ((col - dim_x / 2.0) * 3.0) / dim_x
      c_imag = ((row - dim_y / 2.0) * 3.0) / dim_x * 1.75
      z_real = 0.0
      z_imag = 0.0

      <> Determine convergence through repeated iteration of complex quadratic
      <>   polynomial.
      while complex_norm(z_real, z_imag) < 2.0 and iters < max_iters
        z_tmp = z_real ** 2.0 - z_imag ** 2.0 + c_real
        z_imag = (2.0 * z_imag * z_real) + c_imag
        z_real = z_tmp
        iters = iters + 1
      fin

      if iters == max_iters
        write "+"
      fin

      if iters != max_iters
        write " "
      fin

      col = col + 1.0
    fin

    say " "
    col = 0.0
    row = row + 1.0
  fin
fin

draw_mandelbrot(80.0, 30.0, 500)
