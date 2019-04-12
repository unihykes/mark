字符串转十六进制("FF2"转为0xFF2)

```cpp
int hexCharToInt(char c) 
{  
        if (c >= '0' && c <= '9') return (c - '0'); 
        if (c >= 'A' && c <= 'F') return (c - 'A' + 10); 
        if (c >= 'a' && c <= 'f') return (c - 'a' + 10); 
        return 0; 
} 
 
char* hexstringToBytes(string s) 
{          
        int sz = s.length(); 
        char *ret = new char[sz/2]; 
        for (int i=0 ; i <sz ; i+=2) { 
            ret[i/2] = (char) ((hexCharToInt(s.at(i)) << 4) 
                                | hexCharToInt(s.at(i+1))); 
        } 
        return ret; 
} 
 
string bytestohexstring(char* bytes,int bytelength) 
{ 
  string str(""); 
  string str2("0123456789abcdef");  
   for (int i=0;i<bytelength;i++) { 
     int b; 
     b = 0x0f&(bytes[i]>>4); 
     char s1 = str2.at(b); 
     str.append(1,str2.at(b));           
     b = 0x0f & bytes[i]; 
     str.append(1,str2.at(b)); 
     char s2 = str2.at(b); 
   } 
   return str; 
} 
 
int main() 
{ 
        char s[3] ={'a','b','c'}; 
        std::string result;

        result = bytestohexstring(s,strlen(s)); 

        for(int i=0;i<3;i++)
        {
            printf("%02x", s[i]&0xFF);
        }

        printf("\n%s\n",result.data());

        system("pause");
}q


```