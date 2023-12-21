def symbol?(char)
  !num?(char) && char != "."
end

def num?(char)
  "0123456789".include? char
end

lines = File.readlines(ARGV.first)
total = 0

lines.size.times do |row|
  line = lines[row]
  in_num = false
  current_num = ""
  nums_with_start_index = []
  start_index = -1

  line.each_char.with_index do |char, i|
    if in_num
      # We're already inside a number, see if it's continuing or ending.
      if num?(char)
        # It's continuing, so concatenate.
        current_num << char
      else
        # It's ending, so add it to the list of numbers.
        in_num = false
        nums_with_start_index << [current_num, start_index]
        current_num = ""
      end
    elsif num?(char)
      # We weren't inside a number, but a new one is starting!
      in_num = true
      current_num << char
      start_index = i
    end
  end

  nums_with_start_index.each do |(num, start_index)|
    # Get the index 1 character before the start of the number.
    # Use max to avoid going negative.
    left_index = [start_index - 1, 0].max

    # Get the index 1 character after the end of the number.
    # Use min to avoid going past the end of the array.
    right_index = [start_index + num.size, line.size - 1].min

    # Iterate through all adjacent characters and see if any of them are symbols.
    is_part_num = (left_index..right_index).any? do |col|
      # There's a symbol above this character.
      (row > 0 && symbol?(lines[row - 1][col])) ||

      # There's a symbol below this character.
      ((row + 1) < lines.size && symbol?(lines[row + 1][col])) ||

      # This character itself is a symbol (handles the left/right edges).
      symbol?(lines[row][col])
    end

    # If any are symbols, add the number to the total.
    total += num.to_i if is_part_num
  end
end

puts total
