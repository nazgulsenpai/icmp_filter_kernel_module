#include <linux/types.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/icmp.h>
#include <linux/string.h>
#include <asm/byteorder.h>

static struct nf_hook_ops *nf_tracer_ops = NULL;
static struct nf_hook_ops *nf_tracer_out_ops = NULL;

static unsigned int nf_tracer_handler(void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {
    if(skb==NULL) {
        return NF_ACCEPT;
    }

    struct iphdr * iph;
    iph = ip_hdr(skb);

    if(iph && iph->protocol == IPPROTO_ICMP) {
        struct icmphdr *tcph = icmp_hdr(skb);
        if(tcph->type == ICMP_TIMESTAMP || tcph->type == ICMP_TIMESTAMPREPLY ) {
                return NF_DROP;
        }
    }

    return NF_ACCEPT;
}


static int __init nf_tracer_init(void) {

    nf_tracer_ops = (struct nf_hook_ops*)kcalloc(1,  sizeof(struct nf_hook_ops), GFP_KERNEL);

    if(nf_tracer_ops!=NULL) {
        nf_tracer_ops->hook = (nf_hookfn*)nf_tracer_handler;
        nf_tracer_ops->hooknum = NF_INET_PRE_ROUTING;
        nf_tracer_ops->pf = NFPROTO_IPV4;
        nf_tracer_ops->priority = NF_IP_PRI_FIRST;

        nf_register_net_hook(&init_net, nf_tracer_ops);
    }

    nf_tracer_out_ops = (struct nf_hook_ops*)kcalloc(1, sizeof(struct nf_hook_ops), GFP_KERNEL);

    if(nf_tracer_out_ops!=NULL) {
        nf_tracer_out_ops->hook = (nf_hookfn*)nf_tracer_handler;
        nf_tracer_out_ops->hooknum = NF_INET_LOCAL_OUT;
        nf_tracer_out_ops->pf = NFPROTO_IPV4;
        nf_tracer_out_ops->priority = NF_IP_PRI_FIRST;

        nf_register_net_hook(&init_net, nf_tracer_out_ops);
    }

    return 0;
}

static void __exit nf_tracer_exit(void) {

    if(nf_tracer_ops != NULL) {
        nf_unregister_net_hook(&init_net, nf_tracer_ops);
        kfree(nf_tracer_ops);
    }

    if(nf_tracer_out_ops != NULL) {
        nf_unregister_net_hook(&init_net, nf_tracer_out_ops);
        kfree(nf_tracer_out_ops);
    }
}

module_init(nf_tracer_init);
module_exit(nf_tracer_exit);

MODULE_LICENSE("GPL");
