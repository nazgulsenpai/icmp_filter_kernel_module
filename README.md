# Simple NetFilter kernel module for dropping ICMP types 13 and 14

Scenario: An environment where firewalls manage iptables but lack the granularity to block ICMP by type, but vulnerabilities like CVE-1999-0524 (ICMP Timestamp Response, Reply, Types 13 & 14) must be mitigated 

There are better ways to handle this in most network environments, but I wanted to learn more about kernel development and it worked the first time with only minimal changes from reading the netfilter headers. Can be used as a simple template to adapt to whatever your needs are.

Module code adapted from [Oracle - Introduction to Netfilter](https://blogs.oracle.com/linux/post/introduction-to-netfilter)

rhel_sign.sh based on documentation available at: [RHEL8](https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/8/html/managing_monitoring_and_updating_the_kernel/signing-a-kernel-and-modules-for-secure-boot_managing-monitoring-and-updating-the-kernel#signing-kernel-modules-with-the-private-key_signing-a-kernel-and-modules-for-secure-boot) and [RHEL9](https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/9/html/managing_monitoring_and_updating_the_kernel/signing-a-kernel-and-modules-for-secure-boot_managing-monitoring-and-updating-the-kernel#signing-kernel-modules-with-the-private-key_signing-a-kernel-and-modules-for-secure-boot)

Licensed under GPLv2 to match the licence implications in the Oracle Netfilter article.
