#!/usr/bin/ruby

#learning rate
$n = 0.05

# gradient descent weight update.
# wi_new = wi_old + n*(td - od) sum_over_D(wi_old*xi_d)
def update_weight t, o, x, w 
  raise "Target output size should be equal to data output size" unless t.size == o.size 
  raise "Weigh output size should be equal to Feature size" unless w.size == x[0].size 
  w.each_with_index do |wi,i|
    t.each_with_index do |td,j|
      wo = w[i]
      sum = 0
      # access x[j][i] for j E [0,N] 
      x.each do |xr|
        sum = sum + wo*xr[i]
      end

      w[i] = wo + $n*(td[j] - o[j])*sum
    end
  end
  w
end


def total_error t,o
  raise "Target output size should be equal to data output size" unless t.size == o.size 
  sum = 0
  t.each_with_index do |td, i|
    sum = sum + (td - o[i])
  end
  sum
end


x = [ [2, 3, 4], [3,5,6], [7,8,9]]
t = [1,0,0]
o = [0,1,1]
w = [0.2,0.2,0.2]

print update_weight t,o,x, w
print "\n"
