#include "RIPPackage.h"

DHCPPackageClient::DHCPPackageClient(DHCPMessageStuct *Meassage):DHCPPackageBasic(Meassage)
{
	meassageType = DHCP_DISCOVER;
	memset(&recvMessage, 0, sizeof(recvMessage));
	DHCPFinish = false;
}

int DHCPPackageClient::package(DHCPMessageStuct *Meassage, int MeassageType)
{
	uint8_t mac[] = "52-3B-8C-5C-72-32";//��̬��������MAC��ַ���ڵ��ԡ�
	DHCPMessageStuct *packet = Meassage;
	switch (MeassageType)
	{
	case DHCP_DISCOVER:
		memset(packet, 0, sizeof(DHCPMessageStuct));
		packet->hdr.xid = 0xaaaaaaaa;
		packet->hdr.htype = ETHERNET;
		packet->hdr.hlen = ETHERNET_LEN;
		packet->hdr.hops = 0;
		packet->hdr.ciaddr.address = 0;
		packet->hdr.yiaddr.address = 0;
		packet->hdr.flags = 0x0080;
		packet->hdr.secs = 0x0000;
		packet->hdr.siaddr.address = 0x00000000;
		packet->hdr.giaddr.address = 0;
		memcpy(packet->hdr.chaddr, mac, 18);
		//MACAGet((char*)packet->hdr.chaddr);//��ȡ����MAC��ַ
		memset(packet->hdr.sname, 0, sizeof(packet->hdr.sname));
		memset(packet->hdr.file, 0, sizeof(packet->hdr.file));
		packet->hdr.dhcp_magic = 0x63538263;
		packet->hdr.op = BOOTREQUEST;
		addOption53(packet, MeassageType);
		break;

	case DHCP_REQUEST:
		memset(packet, 0, sizeof(DHCPMessageStuct));
		packet->hdr.op = BOOTREQUEST;
		packet->hdr.htype = ETHERNET;
		packet->hdr.hlen = ETHERNET_LEN;
		packet->hdr.hops = 0;
		packet->hdr.xid = 0x1111111a;
		packet->hdr.ciaddr.address=0;
		packet->hdr.yiaddr.address=0;
		packet->hdr.flags = 0x0080;
		packet->hdr.secs = 0x0000;
		packet->hdr.siaddr.address = 0x00000000;
		packet->hdr.giaddr.address = 0;
		memcpy(packet->hdr.chaddr, mac, 18);
		//MACAGet((char*)packet->hdr.chaddr);
		memset(packet->hdr.sname, 0, sizeof(packet->hdr.sname));
		memset(packet->hdr.file, 0, sizeof(packet->hdr.file));
		packet->hdr.dhcp_magic = 0x63538263;
		addOption53(packet, MeassageType);
		break;

	default:
		break;
	};
	return 0;
}

int DHCPPackageClient::addOption53(DHCPMessageStuct *Meassage, int MeassageType)
{
	DHCPMessageStuct *packet = Meassage;
	packet->option.DHCPMeassageType = MeassageType;
	return 0;

}

void DHCPPackageClient::package()
{

	package(meassage, meassageType);
}

void DHCPPackageClient::addOption53()
{
	addOption53(meassage, meassageType);
}

int DHCPPackageClient::analysis(DHCPMessageStuct *Meassage)
{
	recvMessage = *Meassage;
	cout << "���������ǣ�";
	if (Meassage->option.DHCPMeassageType == 2)
		printf("OFFER\n");
	else if (Meassage->option.DHCPMeassageType == 4)
		printf("ACK\n");
	cout << "����IP��ַ�ǣ�"
		<< (int)Meassage->hdr.yiaddr.seg[3]  << "."
		<< (int)Meassage->hdr.yiaddr.seg[2]<< "."
		<< (int)Meassage->hdr.yiaddr.seg[1] << "."
		<< (int)Meassage->hdr.yiaddr.seg[0] << "."
		<< endl;
	cout << "�����ǣ�"
		<< (int)Meassage->option.subnetMask.seg[3] << "."
		<< (int)Meassage->option.subnetMask.seg[2] << "."
		<< (int)Meassage->option.subnetMask.seg[1] << "."
		<< (int)Meassage->option.subnetMask.seg[0] << "."
		<< endl;
	cout << "�����ǣ�"
		<< (int)Meassage->option.routerAddress.seg[3] << "."
		<< (int)Meassage->option.routerAddress.seg[2] << "."
		<< (int)Meassage->option.routerAddress.seg[1] << "."
		<< (int)Meassage->option.routerAddress.seg[0] << "."
		<< endl;
	cout << "���ʱ��Ϊ��"
		<< (int)Meassage->option.addressLeaseTime[0]<<":"
		<< (int)Meassage->option.addressLeaseTime[1]<< ":"
		<< (int)Meassage->option.addressLeaseTime[2]<< ":"
		<< endl;
	if (recvMessage.option.DHCPMeassageType == DHCP_ACK)
		DHCPFinish = true;
	switch (recvMessage.option.DHCPMeassageType)
	{
	case DHCP_OFFER:
		meassageType = DHCP_REQUEST;
		break;
	case DHCP_ACK:
		meassageType = DHCP_REQUEST;
	default:
		break;
	}

	return 0;
}

bool DHCPPackageClient::getState()
{
	return DHCPFinish;
}