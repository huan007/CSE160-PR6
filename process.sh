#! /bin/bash
rm final
rm final2
for i in {200..4000..200}
do
	(cat time-$i | grep ^real) >> final
done
