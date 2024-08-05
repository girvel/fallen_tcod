local addlib = require("add_lib")

print("-- running tests --")
assert(addlib.add(2, 2) == 4, "2 + 2 should be equal 4")
print("Success!")
