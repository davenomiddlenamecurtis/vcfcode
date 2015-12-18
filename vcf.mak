# Makefile for programs in vcf folder
# the file makes its targets in ../obj
# this means it and source files can live in ../vcfcode which will only be text files

C = gcc
CC = g++

OURFLAGS = $(CFLAGS) 

HEADERS = btree.h consequenceType.hpp dcerror.hpp dcindex.hpp geneVarUtils.hpp getGene.hpp getSequence.hpp intervalList.h masterLocusFile.hpp vcfLocusFile.hpp hapsLocusFile.hpp

ifdef INOBJ
all: groupGetGenotypes genePhaseRec geneTestRec geneVarAssoc groupVarAssoc geneVarAssocAll geneVarAssocSome showAltSubs SNPVarAssoc
else
all:
	if [ ! -e ../obj ] ; then mkdir ../obj ; fi ; \
	cd ../obj; \
	make -f ../vcfcode/vcf.mak INOBJ=INOBJ ; \
	cd ../vcfcode
endif

clean:
	rm *.o

VPATH=../vcfcode
	
%.o: ../vcfcode/%.cpp $(HEADERS)
	$(CC) $(OURFLAGS) -c $< -o ../obj/$@
	
%.o: ../vcfcode/%.c $(HEADERS)
	$(C) $(OURFLAGS) -c $< -o ../obj/$@

groupGetGenotypes: groupGetGenotypes.o btree.o consequenceType.o dcerror.o dcindex.o geneVarUtils.o getGeneFuncs.o getSequenceFuncs.o intervalList.o vcfLocusFile.o vcfWriteVars.o masterLocusFile.o hapsLocusFile.o outputGenotypes.o 
	$(CC) -o groupGetGenotypes groupGetGenotypes.o  btree.o consequenceType.o dcerror.o dcindex.o geneVarUtils.o getGeneFuncs.o getSequenceFuncs.o intervalList.o vcfLocusFile.o vcfWriteVars.o masterLocusFile.o hapsLocusFile.o outputGenotypes.o 

genePhaseRec: genePhaseRec.o btree.o consequenceType.o dcerror.o dcindex.o geneVarUtils.o getGeneFuncs.o getSequenceFuncs.o intervalList.o vcfLocusFile.o vcfWriteVars.o masterLocusFile.o hapsLocusFile.o
	$(CC) -o genePhaseRec genePhaseRec.o  btree.o consequenceType.o dcerror.o dcindex.o geneVarUtils.o getGeneFuncs.o getSequenceFuncs.o intervalList.o vcfLocusFile.o vcfWriteVars.o masterLocusFile.o hapsLocusFile.o

geneTestRec: geneTestRec.o btree.o consequenceType.o dcerror.o dcindex.o geneVarUtils.o getGeneFuncs.o getSequenceFuncs.o intervalList.o vcfLocusFile.o vcfWriteVars.o masterLocusFile.o hapsLocusFile.o
	$(CC) -o geneTestRec geneTestRec.o  btree.o consequenceType.o dcerror.o dcindex.o geneVarUtils.o getGeneFuncs.o getSequenceFuncs.o intervalList.o vcfLocusFile.o vcfWriteVars.o masterLocusFile.o hapsLocusFile.o

geneVarAssoc: geneVarAssoc.o btree.o consequenceType.o dcerror.o dcindex.o geneVarUtils.o getGeneFuncs.o getSequenceFuncs.o intervalList.o vcfLocusFile.o vcfWriteVars.o masterLocusFile.o hapsLocusFile.o
	$(CC) -o geneVarAssoc geneVarAssoc.o btree.o consequenceType.o dcerror.o dcindex.o geneVarUtils.o getGeneFuncs.o getSequenceFuncs.o intervalList.o vcfLocusFile.o vcfWriteVars.o masterLocusFile.o hapsLocusFile.o

groupVarAssoc: groupVarAssoc.o btree.o consequenceType.o dcerror.o dcindex.o geneVarUtils.o getGeneFuncs.o getSequenceFuncs.o intervalList.o vcfLocusFile.o vcfWriteVars.o masterLocusFile.o hapsLocusFile.o
	$(CC) -o groupVarAssoc groupVarAssoc.o btree.o consequenceType.o dcerror.o dcindex.o geneVarUtils.o getGeneFuncs.o getSequenceFuncs.o intervalList.o vcfLocusFile.o vcfWriteVars.o masterLocusFile.o hapsLocusFile.o

geneVarAssocAll: geneVarAssocAll.o btree.o consequenceType.o dcerror.o dcindex.o geneVarUtils.o getGeneFuncs.o getSequenceFuncs.o intervalList.o vcfLocusFile.o vcfWriteVars.o masterLocusFile.o hapsLocusFile.o
	$(CC) -o geneVarAssocAll geneVarAssocAll.o btree.o consequenceType.o dcerror.o dcindex.o geneVarUtils.o getGeneFuncs.o getSequenceFuncs.o intervalList.o vcfLocusFile.o vcfWriteVars.o masterLocusFile.o hapsLocusFile.o

geneVarAssocSome: geneVarAssocSome.o btree.o consequenceType.o dcerror.o dcindex.o geneVarUtils.o getGeneFuncs.o getSequenceFuncs.o intervalList.o vcfLocusFile.o vcfWriteVars.o masterLocusFile.o hapsLocusFile.o
	$(CC) -o geneVarAssocSome geneVarAssocSome.o btree.o consequenceType.o dcerror.o dcindex.o geneVarUtils.o getGeneFuncs.o getSequenceFuncs.o intervalList.o vcfLocusFile.o vcfWriteVars.o masterLocusFile.o hapsLocusFile.o

SNPVarAssoc: SNPVarAssoc.o btree.o consequenceType.o dcerror.o dcindex.o geneVarUtils.o getGeneFuncs.o getSequenceFuncs.o intervalList.o vcfLocusFile.o vcfWriteVars.o masterLocusFile.o hapsLocusFile.o
	$(CC) -o SNPVarAssoc SNPVarAssoc.o btree.o consequenceType.o dcerror.o dcindex.o geneVarUtils.o getGeneFuncs.o getSequenceFuncs.o intervalList.o vcfLocusFile.o vcfWriteVars.o masterLocusFile.o hapsLocusFile.o

showAltSubs: showAltSubs.o btree.o consequenceType.o dcerror.o dcindex.o geneVarUtils.o getGeneFuncs.o getSequenceFuncs.o intervalList.o vcfLocusFile.o vcfWriteVars.o masterLocusFile.o hapsLocusFile.o
	$(CC) -o showAltSubs showAltSubs.o btree.o consequenceType.o dcerror.o dcindex.o geneVarUtils.o getGeneFuncs.o getSequenceFuncs.o intervalList.o vcfLocusFile.o vcfWriteVars.o masterLocusFile.o hapsLocusFile.o

