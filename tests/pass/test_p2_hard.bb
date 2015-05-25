<> The hard test integrates both int and float declaration, assignment,
<>   arithmetic, and commenting. It also shows that IDs can be used as
<>   expressions, and IDs can be assigned recursively.
<> Float arithmetic is tested pretty extensively in the medium case.

<> Float declarations.
float faye
float spike
float jet
float ed
float ein

<> Int calculations we just don't use.
int vicious
int julia
vicious = 1
julia = 1
vicious = julia + vicious
julia = vicious + julia

<> Do some Number foo.
faye = 1.0
spike = 2.0 * faye
jet = 2.0 * spike
ed = 2.0 * jet
ein = 2.0 * ed
faye = 2.0 * ein - 1.0
spike = 2.0 * faye
ed = 2.0 * spike
ein = 2.0 * ed

<> Final calculation.
float bebop
bebop = 2.0 * ein  <>perfect!

<> Print the answer.
say bebop + 0.2
