# vcfcode
Code to manipulate vcf files

Unpack repository into e.g. vcf/vcfcode
cd to vcf/vcfcode
Run:
make -f vcf.mak

Should create obj and executables in vcf/obj and vcf/bin

The documentation to run geneVarAssoc and options is in vcfDocumentation.txt.

There is an example argument file called example.arg. It would need to be edited to point to vcf and reference files which you actually have on your system. Once this was done, one could enter, for example:

showAltSubs --case-file SSSDNMnew.all.vcf.gz --position 6:33410697
