#ifndef CONSEQUENCETYPEHPP
#define CONSEQUENCETYPEHPP

enum consequenceType{
NULL_CONSEQUENCE=0,
INTERGENIC,
DOWNSTREAM,
INTRONIC,
THREEPRIME_UTR,
UPSTREAM,
SYNONYMOUS_CODING,
FIVEPRIME_UTR,
CODINGINDEL,
SPLICE_SITE,
STOP_LOST,
NON_SYNONYMOUS_CODING,
FRAMESHIFT_CODING,
STOP_GAINED,
KOZAK,
NCONSEQUENCETYPES
};

struct consequenceReport_t {
	consequenceType t;
	char *str;
	float weight;
};

typedef struct consequenceReport_t consequenceReport;

extern consequenceReport consequence[];
const char* consequenceString(consequenceType t);

// I’ve talk with Andy about the splicing site definition. 
// Reading literature, we decide that the donor splicing site (moving from exon to intron) we have to consider 5bp in the exon and 6 in the intron. 
// For the acceptor splicing site (moving from intron to exon) we have to consider 20bp in the intron and 3 in the exon. I’ll ask knome their definition of splicing site.
// NSB is Number of Splicesite Bases

#define NSBDONOREXON 5
#define NSBDONORINTRON 6
#define NSBACCEPTOREXON 3
#define NSBACCEPTORINTRON 20
enum spliceSiteType {DONOR,ACCEPTOR};

#endif