lines = File.readlines(ARGV.first)

total = 0

lines.each do |line|
  match = /^Game (\d+): (.*)$/.match(line)
  required = { "red" => 0, "green" => 0, "blue" => 0 }

  match.captures.last.split("; ").each do |reveal|
    reveal.split(", ").each do |count|
      amount, color = count.split(" ")
      required[color] = [required[color], amount.to_i].max
    end
  end

  power = required.values.inject(:*)

  puts "#{power} - #{line.strip}"

  total += power
end

puts "Total: #{total}"
