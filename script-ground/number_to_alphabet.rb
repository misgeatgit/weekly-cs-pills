
@num_alpha_map = {0 =>'zero', 1 => 'one', 2 => 'two', 3 => 'three', 4 => 'four',5 => 'five',
                  6 => 'six', 7 => 'seven', 8 => 'eight', 9 => 'nine',
                  10 => 'ten', 11 => 'eleven', 12 => 'twelve', 13 => 'thirteen',
                  14 => 'fourteen', 15 => 'fifteen', 16 => 'sixteen', 17=>'seventeen',
                  18=>'eighteen',19=>'ninteen', 20 => 'twenty', 30 => 'thirty',
                  40 => 'fourty', 50 => 'fifty', 60 =>'sixty', 70 => 'seventy',
                  80 => 'eighty', 90 => 'ninety', 100 => 'one-hundred'}


def to_lang_en number
  if @num_alpha_map[number]
    return @num_alpha_map[number]
  else
    if number > 10 && number < 20
      return "#{ @num_alpha_map[number%10]}"
    elsif number > 20 && number < 30
      return "twenty-#{ @num_alpha_map[number%20]}"
    elsif number > 30 && number < 40
      return "thirty-#{ @num_alpha_map[number%30]}"
    elsif number > 40 && number < 50
      return "fourty-#{ @num_alpha_map[number%40]}"
    elsif number > 50 && number < 60
      return "fifty-#{ @num_alpha_map[number%50]}"
    elsif number > 60 && number < 70
      return "sixty-#{ @num_alpha_map[number%60]}"
    elsif number > 70 && number < 80
      return "seventy-#{ @num_alpha_map[number%70]}"
    elsif number > 80 && number < 90
      return "eighty-#{ @num_alpha_map[number%80]}"
    elsif number > 90 && number < 100
      return "ninety-#{ @num_alpha_map[number%90]}"
    elsif number > 100 && number < 1000
      return "#{@num_alpha_map[(number/100).to_i]}-hundred and #{to_lang_en(number%100)}"
    elsif number > 1000 && number < 1000000
      return "#{to_lang_en ((number/1000).to_i)}-thousand and #{to_lang_en(number%1000)}"
    else
      return "#{number} is not yet handled. Provide number less than 1000000."
    end
  end
end

#TEST
=begin
print "56 is #{to_lang_en(56)}\n"
print "50 is #{to_lang_en(50)}\n"
print "45 is #{to_lang_en(45)}\n"
print "30 is #{to_lang_en(30)}\n"
print "4 is #{to_lang_en(4)}\n"
print "0 is #{to_lang_en(0)}\n"
print "100 is #{to_lang_en(100)}\n"
print "777 is #{to_lang_en(777)}\n"
print "1777 is #{to_lang_en(1777)}\n"
print "34560 is #{to_lang_en(34560)}\n"
=end
if ARGV[0]
inp = ARGV[0].to_i
print "#{to_lang_en(inp)}\n"
else
  print "Please provide a valid integer number.\n"
end
