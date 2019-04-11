


```
Libcurl为一个免费开源的，客户端url传输库，支持FTP，FTPS，TFTP，HTTP，HTTPS，GOPHER，TELNET，DICT，FILE和LDAP，跨平台，支持Windows，Unix，Linux等，线程安全，支持Ipv6。并且易于使用。
下载地址： http://curl.haxx.se/download.html

./configure –enable-smtp –enable-pop3
make
make install
使用curl –version 查看使用版本是否一样
全局的准备
程序必须初始化一些libcurl的全局函数。这意味着不管你准备使用libcurl多少次，你都应该，且只初始化一次。当你的程序开始的时候，使用
curl_global_init()
这个函数需要一个参数来告诉它如何来初始化。使用CURL_GLOBAL_ALL ,它将用通常是比较好的默认参数来初始化所有已知的内部子模块。还有两个可选值：
CURL_GLOBAL_WIN32
这个参数只被用在windows 操作系统上。它让libcurl初始化win32套接字的的东西。没有正确的初始化，你的程序将不能正确的使用套接字。你应该只为每个程序做一次这样的操作，如果你的程序的其他库这样了，你就不要再让libcurl这样做。
CURL_GLOBAL_SSL
这个参数会使libcurl具有SSL的能力。你应该只为每个程序做一次这样的操作，如果你的程序的其他库这样了，你就不要再让libcurl这样做。
libcurl有个默认的保护机制，检测如果curl_global_init没有在curl_easy_perform之前被调用，那么libcurl会猜测该使用的初始化模式来执行程序。请注意，依靠默认的保护机制来这么做一点都不好。
当程序不再使用libcurl，请调用curl_global_cleanup函数来对应初始化函数所做的工作，它会做逆向的工作来清理curl_global_init所初始化的资源。
请避免重复的调用curl_global_init和 curl_global_cleanup。他们每个仅被调用一次。
libcurl所支持的功能
确定libcurl所提供功能的最佳办法是在运行的时候而不是在编译的时候。通过调用curl_version_info函数，然后查看返回信息的结构体，你知道当前的libcurl版本所支持的功能了。
使用libcurl的简单接口
首先介绍libcurl的简单接口(easy interface)，这些接口都有curl_easy的前缀。 libcurl的最近版本还提供了复杂接口(multi interface)。更多关系该接口的信息将另作讨论，为了更好的理解复杂接口，你仍然需要先了解简单接口。
为了使用简单接口，你先需要创建一个简单接口的句柄。每一个简单接口的数据通信都需要这个句柄。一般来说，你需要为每个准备传输数据的线程使用一个句柄。但你绝不能在多线程里共享相同的句柄。
获取简单句柄
easyhandle = curl_easy_init();
这个函数返回一个简单接口句柄。接下来的操作力，可以在这个`easyhandle设置各种选项。在随后的一个或者多次数据传输中，句柄只是一个逻辑实体。 通过 curl_easy_setopt设置句柄的属性和选项，它们控制随后的数据传输。这些属性和选项的设置一个保存在句柄里直到它再次被设置为其他值。多次网络请求使用相同的句柄，它们的句柄选择和属性也是相同的。
很多用于设置libcurl属性都是字符串，一个指向一段以0结尾数据。当你用字符串设置 curl_easy_setopt(），libcurl会复制这个字符串的一个副本，所以你在设置后不用再保存那个字符串的内存。
在句柄上最经常设置的属性是URL。你可以这样设置它
curl_easy_setopt(handle, CURLOPT_URL, “http://domain.com/”);
假如你希望得到指定URL上的远程主机的数据资源到本地。如果你想自己处理得到的数据而不是直接显示在标准输出里，你可以写一个符合下面原型的函数
size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);
你可以用类似下面这样的代码来控制libcurl将得到的数据传递到你写的函数里
curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION, write_data);
你还可以控制你的回调函数第四个参数得到的数据，用这样的函数原型
curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, &internal_struct);
使用这种原型，你可以很容易在你程序和被libcurl调用函数之间传递本地数据。使用 CURLOPT_WRITEDATA,libcurl不会处理你所传递的数据。
假如你没用使用CURLOPT_WRITEFUNCTION设置回调函数，libcurl会有默认的处理。它只是把接收到的数据输出到标准输出里。你可以使用传递一个FILE *的打开文件参数，设置默认处理函数CURLOPT_WRITEDATA ,它把得到的数据存放在一个文件里。
这里有一个与平台有关的缺陷。有时候libcurl不能操作一个呗程序所打开的文件。如果你用CURLOPT_WRITEDATA给默认的回调函数传递一个打开的文件，程序可能崩溃。(CURLOPT_WRITEDATA 原来的名称为CURLOPT_FILE,它们是同样的工作机理)。
如果你以 win32 dll的方式使用libcurl，如果你设置了，CURLOPT_WRITEDATA ，也必须用CURLOPT_WRITEFUNCTION ，否则你会遇到程序崩溃。 还有其他很多的选项可以设置，我们放在后面再详细讨论，接着往下看
success = curl_easy_perform(easyhandle);
curl_easy_perform函数将会连接远程的站点，发送必要的命令和接受传输的数据。当它收到了数据，它就会调用我们先前设置的回调函数。这个函数可能一次得到一个字节或者几千个字节。libcurl会尽可能多的，尽可能快的传回数据。我们回调函数返回它所得到数据的大小。如果返回的数据大小与传递给它数据大小不一致，libcurl将会终止操作，并返回一个错误代码。
当数据传输完成，curl_easy_perform返回一个代码来告诉你是否成功。如果你仅返回一个代码还不够，你可以使用CURLOPT_ERRORBUFFER ,让libcurl缓存许多可读的错误信息
如果你还想传输其他数据，已有的句柄可以多次使用。记住，鼓励你使用现有的句柄来传输其他数据，libcurl会尝试已经先前已经建立好的连接。
对于某些协议，下载文件可能涉及到很多复杂的协议用来记录信息，设置传输模式，更改当前的目录并最终传递数据。传递一个文件的URL，libcurl会为你掌管所有细节，把文件从一台机器移动到两一台机器。
多线程问题
最基本的原则是绝对不要同时在多个线程之间共享一个libcurl的句柄。确保任何时候一个句柄只是在一个线程里使用。你可以在多个线程之间传递句柄，但是你不能使用。
libcurl是线程安全的，除了以下两种情况：信号量和SSL/TLS句柄。信号量用于超时失效名字解析(在域名解析的时候)。
如果你通过多线程方式来访问HTTPS 或者 FTPS 网址，你可以使用底层的SSL库，多线程库。这些库可能有它们独有的要求，你要多加注意详细参考

OpenSSL
http://www.openssl.org/docs/crypto/threads.html#DESCRIPTION
GnuTLS
http://www.gnu.org/software/gnutls/manual/html_node/Multi_002dthreaded-applications.html
NSS 它宣称是线程安全，没有任何特殊的要求。 PolarSSL 未知。yassl 未知。axTLS 未知。
当你使用多线程的时候，你应当为所有的句柄设置CURLOPT_NOSIGNAL 选项。所有的时候都可以工作正常除了DNS查询超时的时候。 同样，CURLOPT_DNS_USE_GLOBAL_CACHE 也不是线程安全的。
当libcurl实际无法工作
总是有各种原因导致网络传输失败。你可能设置错误的libcurl选项，误解了libcurl某些选项的实际作用，或者远程服务器返回libcurl一个非标准的应答。
当发生错误的时候，这里有一个黄金法:设置CURLOPT_VERBOSE 选项为1。这将导致libcurl显示出所有发送的实体协议的细节，或者还有一些内部的信息和一些收到协议的数据(尤其是 FTP)。如果你使用HTTP ,CURLOPT_HEADER设为1,请求头/响应头也会被输出,这些头信息将出现在消息的内容中。
如果CURLOPT_VERBOSE 还不够，你设置CURLOPT_DEBUGFUNCTION来调试你的数据。
上传数据到远程站点
libcurl尽量保持与协议无关性，就是上传文件到远程的FTP跟用PUT方式上传数据到HTTP服务器和非常类似的。 我们写一个程序，很可能想libcurl按照我们的要求上传数据。我需要设置如下函数原型的读数据的回调函数
size_t function(char *bufptr, size_t size, size_t nitems, void *userp);
bufptr 参数指向一段准备上传数据的缓冲区，nitem是这段缓冲区的大小，userp是一个用户自定义指针，libcurl不对该指针作任何操作，它只是简单的传递该指针。可以使用该指针在应用程序与libcurl之间传递信息。

curl_easy_setopt(easyhandle, CURLOPT_READFUNCTION, read_function);
curl_easy_setopt(easyhandle, CURLOPT_READDATA, &filedata);
Tell libcurl that we want to upload:
curl_easy_setopt(easyhandle, CURLOPT_UPLOAD, 1L);
有几个协议将不能正常工作当上传的时候没有告诉上传文件的大小。所以设置上传文件的大小请使用CURLOPT_INFILESIZE_LARGE

/* in this example, file_size must be an curl_off_t variable */
curl_easy_setopt(easyhandle, CURLOPT_INFILESIZE_LARGE, file_size);
当你调用curl_easy_perform()的时候，libcurl会执行所有的必要动作，当开始上传的时候，它会调用我的回调函数。程序会尽可能多，尽可能快的的上传数据。回调函数返回写入缓冲区的数据的大小。返回0的时候就表示上传结束了。
密码
许多协议要求用户名和密码才能下载或者上传你所选择的数据。libcurl提供了指定的几种方法。
许多协议都支持用户名和密码包含在指定的URL里。libcurl会检测并相应的使用它们。可以按照这样的格式写
protocol://user:password@example.com/path/
如果你的用户名和密码需要一些奇特的字符，你应该使用URLd编码，像%XX，其中ＸＸ是两位十六进制的数字。
libcurl同事也提供了一个设置各种类型密码的选项。设置CURLOPT_USERPWD 选项如下
curl_easy_setopt(easyhandle, CURLOPT_USERPWD, “myname:thesecret”);
在某些情况下可能会多次用到用户名和密码，可以使用代码来验证身份。libcurl提供一个CURLOPT_PROXYUSERPWD选项来实现这种功能,跟CURLOPT_USERPWD 选项很类似
curl_easy_setopt(easyhandle, CURLOPT_PROXYUSERPWD, “myname:thesecret”);
HTTP 认证
先前的章节我们显示了如何为需要验证的URL设置用户和密码。当我们使用HTTP协议的时候，客户端有许多不同的向服务器发送身份验证。最基本的HTTP认证为Basic认证，它发送base64编码的明文用户和密码，这不安全。 如今，libcrul支持使用Basic, Digest, NTLM, Negotiate, GSS-Negotiate and SPNEGO等方式的认证，你可以设置CURLOPT_HTTPAUTH 告诉libcurl使用那种认证。
curl_easy_setopt(easyhandle, CURLOPT_HTTPAUTH, CURLAUTH_DIGEST);
当你想代理服务器认证的时候，你可以使用

CURLOPT_PROXYAUTH:

curl_easy_setopt(easyhandle, CURLOPT_PROXYAUTH, CURLAUTH_NTLM);
你可以组合多种认证方式，libcurl会以合理的方式处理 curl_easy_setopt(easyhandle, CURLOPT_HTTPAUTH, CURLAUTH_DIGEST|CURLAUTH_BASIC);
为了方便起见，你还可以使用CURLAUTH_ANY，它允许libcurl使用任何想要的方法。
HTTP POSTing
HTML最简单的也是最常见的POST是使用<form>这个标签来实现的。我们提供了一个指向数据段 指针，然后告诉licurl把它发送到远程站点：

char *data=“name=daniel&project=curl”;
curl_easy_setopt(easyhandle, CURLOPT_POSTFIELDS, data);
curl_easy_setopt(easyhandle, CURLOPT_URL, “http://posthere.com/”);

curl_easy_perform(easyhandle); /* post away! */
是不是很简单。当你设置了CURLOPT_POSTFIELDS选项，它会自动切换句柄来POST接下的请求。
如果你想发送二进制的数据，需要设置一下数据头，用来知名数据的类型和数据的大小。如下

struct curl_slist *headers=NULL;
headers = curl_slist_append(headers, “Content-Type: text/xml”);

/* post binary data */
curl_easy_setopt(easyhandle, CURLOPT_POSTFIELDS, binaryptr);

/* set the size of the postfields data */
curl_easy_setopt(easyhandle, CURLOPT_POSTFIELDSIZE, 23L);

/* pass our list of custom made headers */
curl_easy_setopt(easyhandle, CURLOPT_HTTPHEADER, headers);

curl_easy_perform(easyhandle); /* post away! */

curl_slist_free_all(headers); /* free the header list */
还有一种是multi-part 表单提交,这被认为是一种更好的方法提交二进制的数据。libcrul同样也支持这种方法。下面是例子:

struct curl_httppost *post=NULL;
struct curl_httppost *last=NULL;
curl_formadd(&post, &last, CURLFORM_COPYNAME, “name”, CURLFORM_COPYCONTENTS, “daniel”, CURLFORM_END);
curl_formadd(&post, &last, CURLFORM_COPYNAME, “project”, CURLFORM_COPYCONTENTS, “curl”, CURLFORM_END);
curl_formadd(&post, &last, CURLFORM_COPYNAME, “logotype-image”, CURLFORM_FILECONTENT, “curl.png”,
CURLFORM_END);

/* Set the form info */
curl_easy_setopt(easyhandle, CURLOPT_HTTPPOST, post);

curl_easy_perform(easyhandle); /* post away! */

/* free the post data again */
curl_formfree(post);
libcurl还允许你在每个定义的部分设置头。下面就是例子

struct curl_slist *headers=NULL;
headers = curl_slist_append(headers, “Content-Type: text/xml”);

curl_formadd(&post, &last, CURLFORM_COPYNAME, “logotype-image”, CURLFORM_FILECONTENT, “curl.xml”,
CURLFORM_CONTENTHEADER, headers, CURLFORM_END);

curl_easy_perform(easyhandle); /* post away! */

curl_formfree(post);
/* free post */
curl_slist_free_all(headers);
/* free custom header list */
所有对简单接口句柄都是“粘的”，这些属性会一直保持不变除非你在调用 curl_easy_perform之前改过。通过将CURLOPT_HTTPGET设为1可以使简单接口句柄回到最原始的状态：
curl_easy_setopt(easyhandle, CURLOPT_HTTPGET, 1L);
只设置CURLOPT_POSTFIELDS 的只为“”或者NULL是不会停止libcurl做POST请求的，这只会做提交空数据的POST。
显示进度
通过将CURLOPT_NOPROCESS设置为0开启进度支持。该选项默认值为1。对大多数应用程序，我们需要提供一个进度显示回调。libcurl会不定期的将当前传输的进度通过回调函数告诉你的程序。

//回调函数原型
int progress_callback(void *clientp, double dltotal,
double dlnow, double ultotal, double ulnow);

/*通过CURLOPT_PROGRESSFUNCTION注册该回调函数。
参数clientp是一个用户自定义指针，应用程序通过CURLOPT_PROCESSDATA
属性将该自定义指定传递给libcurl。libcurl对该参数不作任何处理，
只是简单将其传递给回调函数。*/
libcurl和c++
只有一件需要特别注意的是回调函数不能使类的非静态成员函数。如

class AClass
{
static size_t write_data(void *ptr, size_t size, size_t nmemb,
void *ourpointer)
{
/* do what you want with the data */
}
}
代理
略过，有兴趣请参考原文。
持久化的好处
当需要发送多次请求时，应该重复使用easy handle。
每次执行完curl_easy_perform，licurl会继续保持与服务器的连接。接下来的请求可以使用这个连接而不必创建新的连接（如果目标主机是同一个的话）。这样可以减少网络开销。 即使连接被释放了，libcurl也会缓存这些连接的会话信息，这样下次再连接到目标主机上时，就可以使用这些信息，从而减少重新连接所需的时间。
FTP连接可能会被保存较长的时间。因为客户端要与FTP服务器进行频繁的命令交互。对于有访问人数上限的FTP服务器，保持一个长连接，可以使你不需要排除等待，就直接可以与FTP服务器通信。
libcurl会缓存DNS的解析结果。
在今后的libcurl版本中，还会添加一些特性来提高数据通信的效率。 每个简单接口句柄都会保存最近使用的几个连接，以备重用。默认是5个。可以通过CURLOPT_MAXCONNECTS属性来设置保存连接的数量。
如果你不想重用连接，将CURLOPT_FRESH_CONNECT属性设置为1。这样每次提交请求时，libcurl都会先关闭以前创建的连接，然后重新创建一个新的连接。也可以将CURLOPT_FORBID_REUSE设置为1，这样每次执行完请求，连接就会马上关闭。
libcurl使用HTTP消息头
当使用libcurl发送http请求时，它会自动添加一些http头。我们可以通过CURLOPT_HTTPHEADER属性手动替换、添加或删除相应的HTTP消息头。
例外：以POST的方式向HTTP服务器提交请求时，libcurl会设置该消息头为“100-continue”，它要求服务器在正式处理该请求之前，返回一个”OK”消息。如果POST的数据很小，libcurl可能不会设置该消息头。
自定义的操作
当前越来越多的协议都构建在HTTP协议之上（如：soap），这主要归功于HTTP的可靠性，以及被广泛使用的代理支持（可以穿透大部分防火墙）。 这些协议的使用方式与传统HTTP可能有很大的不同。对此，libcurl作了很好的支持。
cookies
cookie是一个键值对的集合，HTTP服务器发给客户端的cookie，客户端提交请求的时候，也会将cookie发送到服务器。服务器可以根据cookie来跟踪用户的会话信息。cookie有过期时间，超时后cookie就会失效。cookie有域名和路径限制，cookie只能发给指定域名和路径的HTTP服务器。
在libcurl中，可以通过CURLOPT_COOKIE属性来设置发往服务器的cookie：
curl_easy_setopt(easyhandle, CURLOPT_COOKIE, “name1=var1; name2=var2;”);
在实在的应用场景中，你可能需要保存服务器发送给你的cookie，并在接下来的请求中，把这些cookie一并发往服务器。所以，可以把上次从服务器收到的所有响应头信息保存到文本文件中，当下次需要向服务器发送请求时，通过CURLOPT_COOKIEFILE属性告诉libcurl从该文件中读取cookie信息。 设置CURLOPT_COOKIEFILE属性意味着激活libcurl的cookie parser。在cookie parser被激活之前，libcurl忽略所以之前接收到的cookie信息。cookie parser被激活之后，cookie信息将被保存内存中，在接下来的请求中，libcurl会自动将这些cookie信息添加到消息头里，你的应用程序不需要做任何事件。大多数情况下，这已经足够了。需要注意的是，通过CURLOPT_COOKIEFILE属性来激活cookie parser，给CURLOPT_COOKIEFILE属性设置的一个保存cookie信息的文本文件路径，可能并不需要在磁盘上物理存在。 如果你需要使用NetScape或者FireFox浏览器的cookie文件，你只要用这些浏览器的cookie文件的路径来初始化CURLOPT_COOKIEFILE属性，libcurl会自动分析cookie文件，并在接下来的请求过程中使用这些cookie信息。 libcurl甚至能够把接收到的cookie信息保存成能被Netscape/Mozilla的浏览器所识别的cookie文件。通过把这些称为cookie-jar。通过设置CURLOPT_COOKIEJAR选项，在调用curl_easy_cleanup释放easy handle的时候，所有的这些cookie信息都会保存到cookie-jar文件中。这就使得cookie信息能在不同的easy handle甚至在浏览器之间实现共享。


CURLOPT_INFILESIZE: 当你上传一个文件到远程站点，这个选项告诉PHP你上传文件的大小。
CURLOPT_VERBOSE: 如果你想CURL报告每一件意外的事情，设置这个选项为一个非零值。
CURLOPT_HEADER: 如果你想把一个头包含在输出中，设置这个选项为一个非零值。
CURLOPT_NOPROGRESS: 如果你不会PHP为CURL传输显示一个进程条，设置这个选项为一个非零值。
注意：PHP自动设置这个选项为非零值，你应该仅仅为了调试的目的来改变这个选项。
CURLOPT_NOBODY: 如果你不想在输出中包含body部分，设置这个选项为一个非零值。
CURLOPT_FAILONERROR: 如果你想让PHP在发生错误(HTTP代码返回大于等于300)时，不显示，设置这个选项为一人非零值。默认行为是返回一个正常页，忽略代码。
CURLOPT_UPLOAD: 如果你想让PHP为上传做准备，设置这个选项为一个非零值。
CURLOPT_POST: 如果你想PHP去做一个正规的HTTP POST，设置这个选项为一个非零值。这个POST是普通的 application/x-www-from-urlencoded 类型，多数被HTML表单使用。
CURLOPT_FTPLISTONLY: 设置这个选项为非零值，PHP将列出FTP的目录名列表。
CURLOPT_FTPAPPEND: 设置这个选项为一个非零值，PHP将应用远程文件代替覆盖它。
CURLOPT_NETRC: 设置这个选项为一个非零值，PHP将在你的 ~./netrc 文件中查找你要建立连接的远程站点的用户名及密码。
CURLOPT_FOLLOWLOCATION: 设置这个选项为一个非零值(象 ‘Location: ‘)的头，服务器会把它当做HTTP头的一部分发送(注意这是递归的，PHP将发送形如 ‘Location: ‘的头)。
CURLOPT_PUT: 设置这个选项为一个非零值去用HTTP上传一个文件。要上传这个文件必须设置CURLOPT_INFILE和CURLOPT_INFILESIZE选项.
CURLOPT_MUTE: 设置这个选项为一个非零值，PHP对于CURL函数将完全沉默。
CURLOPT_TIMEOUT: 设置一个长整形数，作为最大延续多少秒。
CURLOPT_LOW_SPEED_LIMIT: 设置一个长整形数，控制传送多少字节。
CURLOPT_LOW_SPEED_TIME: 设置一个长整形数，控制多少秒传送CURLOPT_LOW_SPEED_LIMIT规定的字节数。
CURLOPT_RESUME_FROM: 传递一个包含字节偏移地址的长整形参数，(你想转移到的开始表单)。
CURLOPT_SSLVERSION: 传递一个包含SSL版本的长参数。默认PHP将被它自己努力的确定，在更多的安全中你必须手工设置。
CURLOPT_TIMECONDITION: 传递一个长参数，指定怎么处理CURLOPT_TIMEVALUE参数。你可以设置这个参数为TIMECOND_IFMODSINCE 或 TIMECOND_ISUNMODSINCE。这仅用于HTTP。
CURLOPT_TIMEVALUE: 传递一个从1970-1-1开始到现在的秒数。这个时间将被CURLOPT_TIMEVALUE选项作为指定值使用，或被默认TIMECOND_IFMODSINCE使用。
下列选项的值将被作为字符串：

CURLOPT_URL: 这是你想用PHP取回的URL地址。你也可以在用curl_init()函数初始化时设置这个选项。
CURLOPT_USERPWD: 传递一个形如[username]:[password]风格的字符串,作用PHP去连接。
CURLOPT_PROXYUSERPWD: 传递一个形如[username]:[password] 格式的字符串去连接HTTP代理。
CURLOPT_RANGE: 传递一个你想指定的范围。它应该是’X-Y’格式，X或Y是被除外的。HTTP传送同样支持几个间隔，用逗句来分隔(X-Y,N-M)。
CURLOPT_POSTFIELDS: 传递一个作为HTTP “POST”操作的所有数据的字符串。
CURLOPT_REFERER: 在HTTP请求中包含一个’referer’头的字符串。
CURLOPT_USERAGENT: 在HTTP请求中包含一个’user-agent’头的字符串。
CURLOPT_FTPPORT: 传递一个包含被ftp ‘POST’指令使用的IP地址。这个POST指令告诉远程服务器去连接我们指定的IP地址。 这个字符串可以是一个IP地址，一个主机名，一个网络界面名(在UNIX下)，或是‘-’(使用系统默认IP地址)。
CURLOPT_COOKIE: 传递一个包含HTTP cookie的头连接。
CURLOPT_SSLCERT: 传递一个包含PEM格式证书的字符串。
CURLOPT_SSLCERTPASSWD: 传递一个包含使用CURLOPT_SSLCERT证书必需的密码。
CURLOPT_COOKIEFILE: 传递一个包含cookie数据的文件的名字的字符串。这个cookie文件可以是Netscape格式，或是堆存在文件中的HTTP风格的头。
CURLOPT_CUSTOMREQUEST: 当进行HTTP请求时，传递一个字符被GET或HEAD使用。为进行DELETE或其它操作是有益的，更Pass a string to be used instead of GET or HEAD when doing an HTTP request. This is useful for doing or another, more obscure, HTTP request.
注意: 在确认你的服务器支持命令先不要去这样做。
下列的选项要求一个文件描述(通过使用fopen()函数获得)：

CURLOPT_FILE: 这个文件将是你放置传送的输出文件，默认是STDOUT.
CURLOPT_INFILE: 这个文件是你传送过来的输入文件。
CURLOPT_WRITEHEADER: 这个文件写有你输出的头部分。
CURLOPT_STDERR: 这个文件写有错误而不是stderr。

给出一个post的例子

#include <stdio.h>#include <curl/curl.h>#include <string.h>
int main(int argc,char **argv) {
CURL *curl;
CURLcode result;
curl=curl_easy_init();
if(!curl) {
return -1;
}
char *url;
if(argc > 1) {
url=argv[1];
} else {
url="http://10.1.9.140/v/post.php";
}
curl_easy_setopt(curl,CURLOPT_URL,url);
curl_easy_setopt(curl,CURLOPT_POST,1);
char *postfields="name=laomeng188@163.com&age=30";
curl_easy_setopt(curl,CURLOPT_POSTFIELDS,postfields);
curl_easy_setopt(curl,CURLOPT_POSTFIELDSIZE,strlen(postfields));
FILE *fp=fopen("result.htm","w+");
if(!fp) {
perror("fopen");
return -2;
}
curl_easy_setopt(curl,CURLOPT_WRITEDATA,fp);
curl_easy_setopt(curl,CURLOPT_VERBOSE,1);
result=curl_easy_perform(curl);
curl_easy_cleanup(curl);
fclose(fp);
return 0;}

做一次C++封装


#ifndef __HTTP_CURL_H__
#define __HTTP_CURL_H__

#include <string>

class CHttpClient{public:
CHttpClient(void);
~CHttpClient(void);

public:
/**
* @brief HTTP POST请求
* @param strUrl 输入参数,请求的Url地址,如:http://www.baidu.com
* @param strPost 输入参数,使用如下格式para1=val1¶2=val2&…
* @param strResponse 输出参数,返回的内容
* @return 返回是否Post成功
*/
int Post(const std::string & strUrl, const std::string & strPost, std::string & strResponse);

/**
* @brief HTTP GET请求
* @param strUrl 输入参数,请求的Url地址,如:http://www.baidu.com
* @param strResponse 输出参数,返回的内容
* @return 返回是否Post成功
*/
int Get(const std::string & strUrl, std::string & strResponse);

/**
* @brief HTTPS POST请求,无证书版本
* @param strUrl 输入参数,请求的Url地址,如:https://www.alipay.com
* @param strPost 输入参数,使用如下格式para1=val1¶2=val2&…
* @param strResponse 输出参数,返回的内容
* @param pCaPath 输入参数,为CA证书的路径.如果输入为NULL,则不验证服务器端证书的有效性.
* @return 返回是否Post成功
*/
int Posts(const std::string & strUrl, const std::string & strPost, std::string & strResponse, const char * pCaPath = NULL);

/**
* @brief HTTPS GET请求,无证书版本
* @param strUrl 输入参数,请求的Url地址,如:https://www.alipay.com
* @param strResponse 输出参数,返回的内容
* @param pCaPath 输入参数,为CA证书的路径.如果输入为NULL,则不验证服务器端证书的有效性.
* @return 返回是否Post成功
*/
int Gets(const std::string & strUrl, std::string & strResponse, const char * pCaPath = NULL);

public:
void SetDebug(bool bDebug);

private:
bool m_bDebug;};
#endif

#include "httpclient.h"#include "curl/curl.h"#include <string>

CHttpClient::CHttpClient(void) :
m_bDebug(false){

}

CHttpClient::~CHttpClient(void){

}

static int OnDebug(CURL *, curl_infotype itype, char * pData, size_t size, void *){
if(itype == CURLINFO_TEXT)
{
//printf("[TEXT]%s\n", pData);
}
else if(itype == CURLINFO_HEADER_IN)
{
printf("[HEADER_IN]%s\n", pData);
}
else if(itype == CURLINFO_HEADER_OUT)
{
printf("[HEADER_OUT]%s\n", pData);
}
else if(itype == CURLINFO_DATA_IN)
{
printf("[DATA_IN]%s\n", pData);
}
else if(itype == CURLINFO_DATA_OUT)
{
printf("[DATA_OUT]%s\n", pData);
}
return 0;}

static size_t OnWriteData(void* buffer, size_t size, size_t nmemb, void* lpVoid){
std::string* str = dynamic_cast<std::string*>((std::string *)lpVoid);
if( NULL == str || NULL == buffer )
{
return -1;
}

char* pData = (char*)buffer;
str->append(pData, size * nmemb);
return nmemb;}

int CHttpClient::Post(const std::string & strUrl, const std::string & strPost, std::string & strResponse){
CURLcode res;
CURL* curl = curl_easy_init();
if(NULL == curl)
{
return CURLE_FAILED_INIT;
}
if(m_bDebug)
{
curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, OnDebug);
}
curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
curl_easy_setopt(curl, CURLOPT_POST, 1);
curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPost.c_str());
curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);
curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
res = curl_easy_perform(curl);
curl_easy_cleanup(curl);
return res;}

int CHttpClient::Get(const std::string & strUrl, std::string & strResponse){
CURLcode res;
CURL* curl = curl_easy_init();
if(NULL == curl)
{
return CURLE_FAILED_INIT;
}
if(m_bDebug)
{
curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, OnDebug);
}
curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);
/**
* 当多个线程都使用超时处理的时候，同时主线程中有sleep或是wait等操作。
* 如果不设置这个选项，libcurl将会发信号打断这个wait从而导致程序退出。
*/
curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
res = curl_easy_perform(curl);
curl_easy_cleanup(curl);
return res;}

int CHttpClient::Posts(const std::string & strUrl, const std::string & strPost, std::string & strResponse, const char * pCaPath){
CURLcode res;
CURL* curl = curl_easy_init();
if(NULL == curl)
{
return CURLE_FAILED_INIT;
}
if(m_bDebug)
{
curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, OnDebug);
}
curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
curl_easy_setopt(curl, CURLOPT_POST, 1);
curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPost.c_str());
curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);
curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
if(NULL == pCaPath)
{
curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
}
else
{
//缺省情况就是PEM，所以无需设置，另外支持DER
//curl_easy_setopt(curl,CURLOPT_SSLCERTTYPE,"PEM");
curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
curl_easy_setopt(curl, CURLOPT_CAINFO, pCaPath);
}
curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
res = curl_easy_perform(curl);
curl_easy_cleanup(curl);
return res;}

int CHttpClient::Gets(const std::string & strUrl, std::string & strResponse, const char * pCaPath){
CURLcode res;
CURL* curl = curl_easy_init();
if(NULL == curl)
{
return CURLE_FAILED_INIT;
}
if(m_bDebug)
{
curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, OnDebug);
}
curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);
curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
if(NULL == pCaPath)
{
curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
}
else
{
curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
curl_easy_setopt(curl, CURLOPT_CAINFO, pCaPath);
}
curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
res = curl_easy_perform(curl);
curl_easy_cleanup(curl);
return res;}

///////////////////////////////////////////////////////////////////////////////////////////////

void CHttpClient::SetDebug(bool bDebug){
m_bDebug = bDebug;}</pre><p></p><pre></pre><br><br><p></p><br>
```