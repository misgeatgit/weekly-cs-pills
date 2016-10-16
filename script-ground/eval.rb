
input = "1+2*3-1+2+3/3+5+2"
$arr = input.split("")
$op_index = {}

def build_op_index
  op_index = {}
  for i  in  0..$arr.length 
    c = $arr[i]
    if  c == "*" || c == "/" || c == "-" || c=="+"
      if op_index[c]
        op_index[c].push(i)
      else
        op_index[c] = [i]
      end
    end
  end
  $op_index = op_index
end

build_op_index

print "INPUT ARRAY #{$arr} \n"
while $op_index.length !=0 do
  for operator in  ["*","/","-","+"]
    print "OPERATOR #{operator} \n"
    if  $op_index[operator] == nil
      next
    end
    
    while $op_index[operator] do
      for i in $op_index[operator]
        print "OP INDEX: #{$op_index[operator]} \n"
        print "INDEX i = #{i} \n"
        ls = $arr[i-1].to_i
        rs = $arr[i+1].to_i
        print "#{ls}(#{i-1}) #{operator}(#{i}) #{rs}(#{i+1})\n"
        res = 0
        unknown = false
        if operator == '/'
          res = ls/rs
        elsif operator == '*'
          res = ls*rs
        elsif operator == '-'
          res = ls - rs
        elsif operator == '+'
          res = ls + rs
        else
          unknown = true
        end
        if !unknown
          $arr[i-1] = res.to_s
          $arr.delete_at(i)
          $arr.delete_at(i)
        end
        print "INPUT ARRAY #{$arr} \n"
        build_op_index
        break
      end
    end
  end
end

print "FINAL ARR #{$arr} \n"

