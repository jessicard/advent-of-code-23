tot = 0
games = {}

File.foreach("input").with_index do |line, i|
  # Remove Game #:
  line.slice!("Game #{i + 1}: ")
  rds = line.split(";")

  # Set up hash
  games[i + 1] = {}
  games[i + 1]["red"] = 0
  games[i + 1]["blue"] = 0
  games[i + 1]["green"] = 0

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
end

games.each do |key, val|
  pwr = 0
  val.each do |color, amt|
    if pwr == 0
      pwr = amt
    else
      pwr *= amt
    end
  end
  tot += pwr
end

puts tot
