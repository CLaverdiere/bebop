<> Strings are not compatable with math operators.
<> The grammar catches this usually, unless the string is stored in an ID.
<> This test makes sure it catches those tricky IDs.

string s
string t

s = "hi there"
t = "what up"

say s + t
