<> Quick sort

int a[10]

none swap(int l, int r)
  int temp
  temp = a[l]
  a[l] = a[r]
  a[r] = temp
fin

none pr_array(int size)
  int i
  i = 0

  while i < size - 1
    write a[i]
    write ", "
    i = i + 1
  fin

  write a[i]
  say ""

  return
fin

none quick_sort(int l, int size)
  int i
  int store
  int pivot_idx
  int pivot_val

  if size < 2
    return
  fin

  pivot_idx = size / 2
  pivot_val = a[l + pivot_idx]

  swap(l + pivot_idx, l + size - 1)

  i = 0
  store = 0
  while i < size - 1
    if a[l + i] < pivot_val
      swap(l + i, l + store)
      store = store + 1
    fin
    i = i + 1
  fin

  swap(l + size - 1, l + store)

  quick_sort(l, store)
  quick_sort(l + store + 1, size - store - 1)
fin

int size
size = 10
a[0] = 6
a[1] = 5
a[2] = 0
a[3] = 7
a[4] = 9
a[5] = 8
a[6] = 2
a[7] = 3
a[8] = 4
a[9] = 1

write "Unsorted: "
pr_array(size)

quick_sort(0, size)

write "Sorted:   "
pr_array(size)
