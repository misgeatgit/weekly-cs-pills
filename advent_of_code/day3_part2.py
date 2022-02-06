# part 2
def find_line(bits_linez, cmp, cmp2):
  bits_linez = bits_lines
  j = 0
  indices = list(range(len(bits_linez)))
  while len(indices) > 1 and j < len(bits_linez[0]):
      cnt = 0
      for i in indices:
        bit = bits_linez[i][j]
        cnt += (int(bit)*-1 if int(bit) == 1 else 1)
      #print("cnt ", cnt)
      val = 1 if cmp2(cnt) else 0
      new_indices = []
      # Filter
      for i in indices:
          if cmp(int(bits_linez[i][j]),val):
            print("col=",j," selected ", bits_linez[i], "cnt ", val)
            new_indices.append(i)
      indices = new_indices
      #print("new_indices ",indices)
      j += 1

  return indices

def to_int(bits):
    n = int(bits[-1])
    for i in range(len(bits)-1):
        n += int(bits[i])*(2**(len(bits)-1-i))
    return n

bits_lines = []
input_base_dir = "."
input_file = f'{input_base_dir}/input_d3.txt'
with open(input_file,'r') as inp:
    for bits in inp.readlines():
        bits_lines.append(bits.strip('\n'))

o2_indices = find_line(bits_lines, lambda a, b: a == b, lambda cnt: cnt <= 0)
co2_indices = find_line(bits_lines, lambda a, b: a != b, lambda cnt: cnt < 0)
print(bits_lines[o2_indices[0]], bits_lines[co2_indices[0]])
n1,n2 = to_int(bits_lines[o2_indices[0]]), to_int(bits_lines[co2_indices[0]])
print(n1, n2)
print( n1 * n2 )
