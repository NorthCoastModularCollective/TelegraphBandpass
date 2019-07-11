import("stdfaust.lib");

inputGain = 0.5;
frequency = nentry("frequency",440,0,100,0.01) : si.smoo;
Q = nentry("Q",1,0,1,0.01) : si.smoo;
g = nentry("g",10.7,0,100,0.01) : si.smoo;
phaseOffset = nentry("phaseOffset",10.7,0,100,0.01) : si.smoo;
process (x) = fi.resonbp(frequency,Q,inputGain,x+_)~cos(phaseOffset+_*(g)); 