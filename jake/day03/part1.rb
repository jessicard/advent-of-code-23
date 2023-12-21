def symbol?(char)
  !(".0123456789".include?(char))
end

lines = File.readlines(ARGV.first)
total = 0

lines.size.times do |row|
  line = lines[row]

  line.scan(/\d+/).each do |num|
    # Get the full match data, not just the string
    match_data = Regexp.last_match
    # num = match_data.to_s
    puts "matched #{num}"

    # Get the index 1 character before the match started.
    # Use max to avoid going negative.
    puts "last match: #{match_data.inspect}"
    left_index = [match_data.offset(0)[0] - 1, 0].max

    puts "left_index = #{left_index}"

    # Get the index 1 character after the match ended.
    # Use min to avoid going past the end of the array.
    right_index = [left_index + num.size, line.size - 1].min

    puts "right_index = #{right_index}"

    is_part_num = false

    if symbol?(line[left_index])
      # There's a symbol on the left
      puts "found symbol on left"
      is_part_num = true
    elsif symbol?(line[right_index])
      # There's a symbol on the right
      puts "found symbol on right"
      is_part_num = true
    else
      # Check if there are any symbols above or below any characters
      left_index.upto(right_index) do |col|
        if row > 0 && symbol?(lines[row - 1][col])
          # There's a symbol above this character.
          puts "found symbol above"
          is_part_num = true
          break
        elsif (row + 1) < lines.size && symbol?(lines[row + 1][col])
          # There's a symbol below this character.
          puts "found symbol below"
          is_part_num = true
          break
        end
      end
    end

    puts

    total += num.to_i if is_part_num
  end
end

puts total
