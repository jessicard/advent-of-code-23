tot = 0
games = {}

File.foreach("input-sm").with_index do |line, i|
  # Remove Game #:
  line.slice!("Game #{i + 1}: ")
  rds = line.split(";")

  # Set up hash
  games[i + 1] = {}
  games[i + 1]["red"] = 0
  games[i + 1]["blue"] = 0
  games[i + 1]["green"] = 0

  # Set up test case
  test = {}
  test["red"] = 12
  test["green"] = 13
  test["blue"] = 14

  rds.each do |rd|
    rd = rd.strip.split(", ")
    rd.each do |grab|
      color = grab.tr('^A-Za-z', '')
      amt = Integer(grab.tr('^0-9', ''))
      if amt > games[i + 1][color]
        games[i + 1][color] = amt
      end
    end
  end

  games.each do |key, arr|
    arr.each do |color, val|
      if arr[color] > test[color]
        puts "Game #{key} fails from #{color} being #{arr[color]}"
        games.delete(i + 1)
        break
      end
    end
  end
end

games.each do |key, arr|
  puts key, arr
  tot += key
end

puts tot
