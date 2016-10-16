
def normalize_10 val
  weight = (val/10).to_i
  if val % 10 != 0
    weight += 1
  end
  weight
end


print normalize_10 56
print normalize_10 60 
