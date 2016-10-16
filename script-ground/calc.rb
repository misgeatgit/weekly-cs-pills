
input = "(1+2+3+(2+2))"
print "Input #{input} \n"
stack = []
input.split("").each do |c|
  if c != ')'
    stack.push(c)
  elsif c == ')'
    
    retval = 0
    loop do
      result = 0
      #order matters.
      rs = stack.pop().to_i

      op = stack.pop()
      if op == '*'
        ls = stack.pop().to_i
        #print "expr: #{ls} #{op} #{rs} \n"
        result = rs * ls
      elsif op == '+'
        ls = stack.pop().to_i

        result = rs + ls
      elsif op == '-'
        ls = stack.pop().to_i
        
        result = ls - rs
      elsif op == '/'
        ls = stack.pop().to_i
      
        result = ls / rs
      else
        break # i.e (result end of global local scope
      end
      stack.push(result) #reduce local stack
      print "STack update #{stack} \n"
      retval = result #update return value
      break if false
    end
      stack.push(retval)
  end
end

print stack 
print "\n"


#TODO
#WORK ON OPERATOR PRECEDENCE IN THE INNER MOST SCOPE. THEN THIS WILL BE A FULLY FLEDEGED CALCULATOR.
