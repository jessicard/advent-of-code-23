lines = File.readlines(ARGV.first)
total = lines.size

puts "Lines: #{total}"

max_counts = {
  "red" => 12,
  "green" => 13,
  "blue" => 14
}

total = 0

lines.each do |line|
  match = /^Game (\d+): (.*)$/.match(line)
  game_id = match.captures.first
  reveals = match.captures.last.split("; ").map do |reveal|
    counts = { "red" => 0, "green" => 0, "blue" => 0 }
    reveal.split(", ").each do |count|
      amount, color = count.split(" ")
      counts[color] += amount.to_i
    end

    counts
  end

  possible = reveals.all? { |r| r.all? { |(color, count)| max_counts[color] >= count }}

  puts "#{line.strip} - #{possible}"

  if possible
    total += game_id.to_i
  end
end

puts "Total: #{total}"
