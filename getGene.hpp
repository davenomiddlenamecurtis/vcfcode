#ifndef GETGENEHPP
#define GETGENEHPP
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dcerror.hpp"
#include "intervalList.h"

#define PROMOTERLENGTH 1000 
#define DOWNSTREAMLENGTH 1000
// defaults
#define MAXEXONPERGENE 1000
#define MAXTRANSCRIPTPERGENE 100
#define NSPLICEBASES 6

// assume all starts 0-based, all ends 1-based, variants etc. 1-based

#include "getSequence.hpp"
#include "consequenceType.hpp"

class varEffect {
public:
int posInCDS,nConsequence;
consequenceType consequence[5];
char aaStr[10],codonStr[10],spliceStr[(NSBACCEPTOREXON+NSBACCEPTORINTRON)*2+10];
varEffect() {;}
void clear (){ nConsequence=0; aaStr[0]=codonStr[0]=spliceStr[0]='\0'; posInCDS=0;}
};

class refseqTranscript {
friend class refseqGeneInfo;
char strand;
int txStart, txEnd,cdsStart,cdsEnd;
	char geneName[100],chr[10];
	int exonCount;
	int exonStarts[MAXEXONPERGENE],exonEnds[MAXEXONPERGENE];
	varEffect effect;
	int getEffect(faSequenceFile &f,int pos,char *all0,char *all1,int promoterLength=PROMOTERLENGTH,int downstreamLength=DOWNSTREAMLENGTH,int getKozak=0);
	int getCodingEffect(faSequenceFile &f,int pos,char *all0,char *all1);
	int getSpliceSiteSequence(faSequenceFile &f,int sSStart,int sSEnd,spliceSiteType sST, bool essential, int pos,char *a0,char *a1);
	int checkExonLengths();
public:
	int read(char *s);
	int getChrNum() { return chr[3]=='Y'?24:chr[3]=='X'?23:atoi(chr+3); } // chr21
	char *getChr() { return chr; }
	int getTxStart() { return txStart; }
	int getTxEnd() {return txEnd; }
	char getStrand() { return strand; }
	int getCdsStart() { return cdsStart; }
	int getCdsEnd() { return cdsEnd; }
	int get3PrimeMatches (faSequenceFile &f,intervalList &matches,char *toMatch);
	void print3PrimeSequence(faSequenceFile &f,FILE *fp);
};

class writeBedFilePar {
public:
	int writeKozaks,writePromoters,writeSpliceSites,writeExons,write5UTR,write3UTR;
	writeBedFilePar() { writeKozaks=writePromoters=writeSpliceSites=writeExons=write5UTR=write3UTR=0; }
};

#define GENELINELENGTH 50000
class refseqGeneInfo {
friend class ggParams;
	varEffect worstEffect;
	consequenceType worstConsequence;
	char geneListFileName[200];
	FILE *geneListFile;
	char baitsFileName[200];
	FILE *baitsFile;
	int baitMargin; // correction to add to listings in baits file to get actual bait coordinates
	char geneName[100];
	static char geneLine[GENELINELENGTH];
	char chr[10];
	int gotAllExons,allExonCount;
	int exonStarts[MAXEXONPERGENE],exonEnds[MAXEXONPERGENE];
	int firstExonStart,lastExonEnd;
	int upstream,downstream;
	char strand;
	char quickFeatureBuff[100],referencePath[100];
	int nTranscript;
	refseqTranscript transcript[MAXTRANSCRIPTPERGENE];
	void getAllExons();
public:
	void setReferencePath(char *s);
	int getChrNum() { return chr[3]=='Y'?24:chr[3]=='X'?23:atoi(chr+3); } // chr21
	char *getChr() { return chr; }
	int getStart() { return firstExonStart; } 
	int getEnd() { return lastExonEnd; } 
	char *getGene() { return geneName; }
	void setUpstream(int u) { upstream=u; }
	void setDownstream(int d) { downstream=d; }
	int getUpstream() { return upstream; }
	int getDownstream() { return downstream; }
	void setBaitMargin(int m) { baitMargin=m; }
	int findFirstGene(char *chrToFind,int posToFind);
	char getStrand() { return strand; }
	int goToStart();
	int findGene(char *name);
	int getNextGene(int transcriptionStartCanVary=1);
	int checkExonLengths();
	refseqGeneInfo() { upstream=downstream=baitMargin=0; geneListFile=0; geneListFileName[0]='\0'; baitsFile=0; baitsFileName[0]='\0'; chr[0]='\0'; nTranscript=0; }
	~refseqGeneInfo() { geneListFile && fclose(geneListFile); baitsFile && fclose(baitsFile); }
	void setListFile(char *fn) { strcpy(geneListFileName,fn); }
	void setBaitsFile(char *fn) { strcpy(baitsFileName,fn); }
	int tbiExtractGene(char *tbiFn,char *outFn,int appendToOld=0,int addChrInVCF=0);
	consequenceType getEffect(int pos,char *all0,char *all1,int promoterLength=PROMOTERLENGTH,int downstreamLength=DOWNSTREAMLENGTH,int getKozak=0);
	const char *tellEffect();
	consequenceType tellWorstConsequence() { return worstConsequence; }
	int writeBedFile(FILE *fo,writeBedFilePar &wbfp);
	int writeBedFile(FILE *fo,writeBedFilePar &wbfp,char *arrayName);
	void getFivePrime(int *st,int *en,int t);
	void getThreePrime(int *st,int *en,int t);
	int getNTranscript() { return nTranscript; }
};

class geneExtractor {
	char variantFileName[200];
public:
	geneExtractor() { variantFileName[0]='\0'; }
	void setVariantFileName(char *s) { strcpy(variantFileName,s); }
	int downloadGene(refseqGeneInfo &r,char *outFn); // from 1000 genomes
	int extractGene(refseqGeneInfo &r,char *outFn,int appendToOld=0,int addChrInVCF=0); // from local file
};

#ifndef DEFAULTVARIANTFILENAME
#define DEFAULTVARIANTFILENAME "ftp://ftp.1000genomes.ebi.ac.uk/vol1/ftp/release/20110521/ALL.chr.phase1_release_v2.20101123.snps_indels_svs.vcf.gz"
#endif

#endif