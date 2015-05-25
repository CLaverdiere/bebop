fmt_decimal: db "%ld", 0
fmt_decimal_nl: db "%ld", 10, 0
fmt_float: db "%lf", 0
fmt_float_nl: db "%lf", 10, 0
fmt_string: db "%s", 0
fmt_string_nl: db "%s", 10, 0

array_oob_str: db "Array out of bounds error: gave index %d to array of size %d", 10, 0
