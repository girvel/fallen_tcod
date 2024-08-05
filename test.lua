local tcod = require("fallen_tcod")

print("-- running tests --")
assert(tcod.add(2, 2) == 4, "2 + 2 should be equal 4")
print("Success!")
