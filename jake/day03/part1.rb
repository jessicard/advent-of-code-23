def symbol?(char)
  !num?(char) && char != "."
end

def num?(char)
  "0123456789".include? char
end

lines = File.readlines(ARGV.first)
total = 0
symbols = []
line_lengths = []

lines.size.times do |row|
  line = lines[row].strip
  line_lengths << line.size

  puts "Line #{row + 1}:"
  puts line

  in_num = false
  current_num = ""
  nums_with_start_index = []
  start_index = -1
  row_total = 0

  line.each_char.with_index do |char, i|
    finish_num = false

    if in_num
      # We're already inside a number, see if it's continuing or ending.
      if num?(char)
        # It's continuing, so concatenate.
        current_num << char
      end

      if i >= line.size - 1 || !num?(char)
        # It's ending (either because we're at the end of a line or we hit a
        # non-number char), so add it to the list of numbers.
        finish_num = true
      end
    elsif num?(char)
      # We weren't inside a number, but a new one is starting!
      in_num = true
      current_num << char
      start_index = i

      # Handle the case where the line ends with a single digit.
      finish_num = i >= line.size - 1
    end

    # If this character was the end of a number, add it to the list and reset
    # all the tracking vars.
    if finish_num
      finish_num = false
      in_num = false
      nums_with_start_index << [current_num, start_index]
      current_num = ""
    end
  end

  # Verify parsing with a parsing method that skips index tracking.
  split_parse = line.split(/[^0-9]+/).reject(&:empty?).inspect
  real_parse = nums_with_start_index.map(&:first).inspect

  if split_parse != real_parse
    puts "BAD PARSE"
    puts "split: #{split_parse}"
    puts "real : #{real_parse}"
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
      if row > 0 && symbol?(lines[row - 1][col])
        # There's a symbol above this character.
        symbols << lines[row - 1][col]
        true
      elsif (row + 1) < lines.size && symbol?(lines[row + 1][col])
        # There's a symbol below this character.
        symbols << lines[row + 1][col]
        true
      elsif symbol?(lines[row][col])
        # This character itself is a symbol (handles the left/right edges).
        symbols << lines[row][col]
        true
      else
        false
      end
    end

    # If any are symbols, add the number to the total.
    row_total += num.to_i if is_part_num
    total += num.to_i if is_part_num
  end

  puts "Total: #{row_total} (row), #{total} (accumulated)"
end

# Verify the characters that were considered symbols.
puts "Symbols: #{symbols.uniq}"

# Verify that all lines were the same length.
puts "Line lengths: #{line_lengths.uniq}"

puts "Answer: #{total}"
