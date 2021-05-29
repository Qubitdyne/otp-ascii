# otp-ascii
One-Time Pad ASCII Quaternion Manifold Utilities

## otp-ascii-gen
One-time Pad ASCII Quaternion Based Manifold Generator.

Summary: otp-ascii manifolds represent a base 94 four-dimensional quaternionic projective space of planes ab, cd, ac, bd, i, j, and k. There are also three additional base 10 number sequences encoded into planes xn, yn, and nn. 20 pre-generated base 94 pseudorandom keys and four SHA 512/256 hashes are also provided. The pre-generated pseudorandom keys function as encryption cipher encoding switches for the quaternion number system, and regular expression pattern matching and transliteration can be used to arbitrarily manipulate encryption cipher encoding switches, allowing in excess of 94<sup>94</sup> unique permutations per pad. The machine's MAC address and a simple memorizable private passphrase are further used as two additional cipher encoding switches for generating unique keys. The pads are encoded and referenced via their epoch timestamp, and they're intended to be changed on a regular basis, i.g. month. This allows a user to recycle straightforward memorizable passphrases as there is no pragmatic way to derive the original passphrase by using matrix operations on systems of equations, even if you had a quantum computer.

Planes:
  - ab = +x
  - cd = -x
  - ac = +y
  - bd = -y
  - i = +z
  - j = -z
  - ij = k = complex imaginary number plane

Legend (lines 21-23, columns 1-5):

![image](https://user-images.githubusercontent.com/22720196/120063187-94f2d100-c02b-11eb-8de5-121af6989181.png)

Legend|Col 1|Col 2|Col 3|VCTR||Col 4|Col 5|VCTR
-|-|-|-|-|-|-|-|-
Line 21|a|#|b|+x||#|#|Undef
Line 22|#|k|i|i=➰||x|y|Undef
Line 23|c|j|d|-x||n|n|mod 10|
VCTR|+y|j=➰|-y|ij=k=➿||mod 10|mod 10|VCTR

Details:
Keys 00, 01, 02, ..., 19: Pseudorandom ASCII Character Sequences 33 to 126, 94 characters in length

Indexed planes:
  - Horizontal:
      - ab: ASCII Character Sequence, 33 to 126
      - cd: ASCII Character Sequence, 126 to 33
  - Vertical:
      - ac: ASCII Character Sequence, 33 to 126
      - bd: ASCII Character Sequence, 126 to 33
      - xn: ASCII Number Sequence, 0 to 9
      - yn: ASCII Number Sequence, mod 10
      - nn: ASCII Number Sequence, 00 to 93
  - Complex:
      - i: ASCII Character Sequence, 33 through 126, randomly shuffled
      - j: ASCII Character Sequence, 33 through 126, randomly shuffled
      - k: Product of i * j
    
Graph: Pseudorandom 94 by 94 Matrix, ASCII Characters 33 to 126

Hashes:
 - SHA01: SHA 512/256 of Keys 00 through 19; otp-ascii string; epoch timestamp
 - SHA02: SHA 512/256 of Indexes and Graph; otp-ascii string; epoch timestamp
 - SHA03: SHA 512/256 of All Keys, Indexes, and Graph; otp-ascii string; epoch timestamp
 - SHA04: SHA 512/256 of Entire contents of otp-ascii-$(timestamp).txt file, written to otp-ascii-$(timestamp).sha


Example Graph:

![image](https://user-images.githubusercontent.com/22720196/120057348-f0ab6300-c007-11eb-92ae-edb609560261.png)

