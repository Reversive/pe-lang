from pe_analyzer import PEAnalyzer
import json

p = PEAnalyzer("./binaries/setup.exe")
p = p.analyze()
print(p)
b_0 = 5
if b_0 == 5:
	b_0 = 10
	print(b_0)
