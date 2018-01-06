#include "unpcap.h"
#include <map>

#define MAXTIME 50000
#define ISUSR(ip) (((ip) & 0xffff0000) == 0xc0a80000)

using namespace std;

map<int, int> users;
struct in_addr in;
long first_intv = 0, last_intv = 0, cur_intv = 0;
long interval;
int usrnum = 0, pktnum = 0;

struct Intv {
	uint32_t usrnum;
	uint32_t traffic;
	uint32_t pktnum;
} intv[MAXTIME];

void count_intv(u_char *user, const struct pcap_pkthdr *h, const u_char *pkt) {
	cur_intv = h->ts.tv_sec / interval;
	if(first_intv == 0) first_intv = last_intv = cur_intv;

	// Only consider a protocol stack of Ethernet, IPv4 and TCP
	// We can get a pointer pointing to each header
	const struct Ethernet *link = (struct Ethernet *)pkt;
	const struct Ipv4 *net = (struct Ipv4 *)(pkt + sizeof(struct Ethernet));
	if(net->version != 0x4) return;
	// IP address in integer
	const int srcip = ntohl(net->srcip);
	const int dstip = ntohl(net->dstip);

	if(ISUSR(srcip)) users.insert(make_pair(srcip, 0));
	if(ISUSR(dstip)) users.insert(make_pair(dstip, 0));

	if(cur_intv == last_intv) {
		intv[cur_intv - first_intv].traffic += h->len;
		intv[cur_intv - first_intv].pktnum++;
	}
	else {
		intv[cur_intv - first_intv - 1].usrnum = users.size();
		users.clear();
		last_intv = cur_intv;
	}
}

int main(int argc, char *argv[]) {
	u_char err[100];
	int i, j;

	if(argc != 3) {
		printf("usage: interval <interval>(second) <filename>\n");
		exit(0);
	}

	interval = atol(argv[1]);
	FILE *fp = fopen(argv[2], "r");
	if(!fp) {
		printf("File does not exist\n");
	}

	pcap_t *pcap = pcap_fopen_offline(fp, NULL);
	pcap_loop(pcap, 0, count_intv, err);

	printf("Time/minute,Users,Traffic,Packet\n");
	int tot_intv = cur_intv - first_intv;
	for(int i = 1; i <= tot_intv - 1; i++) {
		printf("%d,%d,%d,%d\n", i, intv[i].usrnum, intv[i].traffic, intv[i].pktnum);
	}
	return 0;
}