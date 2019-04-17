# atom设置

## 颜色RGB查询
https://m.fontke.com/tool/rgb/abb3bf/

## 用户设置
config.cson 备份至:2019-4-11
```cson

"*":
  "autocomplete-plus":
    autoActivationDelay: 3
  "bracket-matcher":
    autocompleteBrackets: false
    highlightMatchingLineNumber: true
  core:
    allowPendingPaneItems: false
    closeDeletedFileTabs: true
    disabledPackages: [
      "whitespace"
      "spell-check"
      "welcome"
      "timecop"
      "language-yaml"
      "language-typescript"
      "language-toml"
      "language-sass"
      "language-ruby-on-rails"
      "language-ruby"
      "language-php"
      "language-perl"
      "language-objective-c"
      "language-mustache"
      "language-less"
      "language-javascript"
      "language-java"
      "language-hyperlink"
      "language-css"
      "language-csharp"
      "language-coffee-script"
      "language-clojure"
      "metrics"
      "exception-reporting"
      "bookmarks"
      "background-tips"
      "autoflow"
      "autocomplete-css"
      "autocomplete-html"
      "autocomplete-atom-api"
      "markdown-preview"
      "autocomplete-plus"
    ]
    packagesWithKeymapsDisabled: [
      "bracket-matcher"
    ]
    telemetryConsent: "no"
    themes: [
      "one-light-ui"
      "one-dark-syntax"
    ]
    uriHandlerRegistration: "always"
  editor:
    autoIndentOnPaste: false
    fontSize: 12
    invisibles:
      cr: " "
      eol: " "
      tab: "â†’"
    lineHeight: 1.1
    preferredLineLength: 100
    scrollPastEnd: true
    showIndentGuide: true
    showInvisibles: true
    tabLength: 4
    tabType: "hard"
  "exception-reporting":
    userId: "fb7193ae-67e0-479a-ae72-e9dad3b0861b"
  "find-and-replace":
    autocompleteSearches: true
    closeFindPanelAfterSearch: true
    projectSearchResultsPaneSplitDirection: "down"
    scrollToResultOnLiveSearch: true
  "highlight-selected":
    highlightBackground: true
  "markdown-preview":
    breakOnSingleNewline: true
    useGitHubStyle: true
  "markdown-preview-enhanced": {}
  "one-dark-ui":
    stickyHeaders: true
    tabSizing: "Minimum"
  "plantuml-viewer":
    charset: "utf-8"
    graphvizDotExecutable: "C:\\Program Files (x86)\\Graphviz2.38\\bin\\dot.exe"
  "platformio-ide-terminal":
    core:
      autoRunCommand: "cd U:\\unihykes\\Apollo_Unique\\apollo\\cmake\\tools"
      shell: "C:\\Windows\\System32\\cmd.exe"
    style:
      theme: "one-dark"
  welcome:
    showOnStartup: false



```

## 用户样式设置:
styles.less
```less
// style the background color of the tree view
.tree-view {
    // background-color: whitesmoke;
    background-color: RGB(208, 255, 255);//目录树背景色
}

// style the background and foreground colors on the atom-text-editor-element itself
atom-text-editor {
    // color: white;//前景色(普通字体颜色)
    background-color: RGB(208, 255, 255);//编辑框背景色
}

// style UI elements inside atom-text-editor
atom-text-editor .cursor {
     border-color: blue;//光标颜色
}

//注释风格
atom-text-editor .syntax--comment {
    font-style:normal; //将注释的斜体修改为正常体
    font-size: 12px; //注释字号
    color:  #2C713C; //注释颜色
}
```


## atom常用插件
#### auto-encoding
#### highlight-selected
#### language-cmake

#### language-plantuml
#### plantuml-viewer
    快捷键ctrl+alt+P(可能会和网易云音乐冲突)
    
    语法教程:http://plantuml.com/class-diagram
    安装教程:https://blog.csdn.net/github_36409600/article/details/73522019
    使用教程:https://www.cnblogs.com/Jeson2016/p/6837186.html
    

    需要额外安装:graphviz:
    http://www.graphviz.org/download/
    
    需要额外安装java:
    https://www.java.com/zh_CN/
    https://sourceforge.net/projects/plantuml/files/plantuml.jar/download
    
    配置:
    charset设置为utf8
    Graphviz Dot Excutable路径:C:\Program Files (x86)\Graphviz2.38\bin\dot.exe
    
#### simlified-chinese-menu

#### language-thrift

#### language-batch

#### markdown-preview-enhanced
应该是ATOM最好、功能最强的Markdown插件

#### language-gfm-enhanced
Markdown语法高亮

#### scroll-marker
滚动条显示改动

#### platformio-ide-terminal
控制台命令行插件
shell override设置为:C:\Windows\System32\cmd.exe
cmd窗口打开,勾选切换到旧版控制台,不然会有乱行问题;
alt+shift+t:打开新控制台
alt+shift+j:切换到左边控制台
alt+shift+k:切换到右边控制台
alt+shift+x:关闭当前控制台
设置快捷键:alt+shift+h用于和隐藏控制台
'atom-text-editor': 
	'alt-shift-h': 'platformio-ide-terminal:toggle'

	