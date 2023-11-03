// 只能读int
#define getcha() (S==T&&(T=(S=fsr)+fread(fsr,1,1<<15,stdin),S==T)?EOF:*S++)
char fsr[1<<15],*S=fsr,*T=fsr;
inline int read(){
	int r(0),w(1);char ch;
	while(ch=getcha(),ch>=58 || ch<=47)w=(ch=='-'?-1:1);r=(r<<3)+(r<<1)+ch-48;
	while(ch=getcha(),ch<=57 && ch>=48)r=(r<<3)+(r<<1)+ch-48;
	return r*w;
}