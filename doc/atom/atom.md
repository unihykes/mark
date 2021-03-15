# atom设置

## 颜色RGB查询
https://m.fontke.com/tool/rgb/abb3bf/

## 用户设置
config.cson 备份至:20201-1-7

```cson

"*":
  "auto-encoding":
    disallowEncTypes: "GBK"
    forceEncTypes: "windows 1252:GBK"
  "autocomplete-plus":
    autoActivationDelay: 3
  "bracket-matcher":
    autocompleteBrackets: false
    highlightMatchingLineNumber: true
  core:
    closeDeletedFileTabs: true
    disabledPackages: [
      "whitespace"
      "spell-check"
      "welcome"
      "timecop"
      "language-yaml"
      "language-typescript"
      "language-sass"
      "language-ruby-on-rails"
      "language-ruby"
      "language-php"
      "language-perl"
      "language-objective-c"
      "language-mustache"
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
      "autocomplete-plus"
      "package-generator"
      "language-rust-bundled"
      "language-go"
      "language-gfm"
      "markdown-preview"
      "language-c"
    ]
    packagesWithKeymapsDisabled: [
      "bracket-matcher"
    ]
    reopenProjectMenuCount: 10
    telemetryConsent: "no"
    themes: [
      "one-light-ui"
      "one-light-syntax"
    ]
    uriHandlerRegistration: "always"
  editor:
    autoIndentOnPaste: false
    invisibles: {}
    lineHeight: 1.1
    preferredLineLength: 100
    scrollPastEnd: true
    showIndentGuide: true
    showInvisibles: true
    tabLength: 4
    tabType: "soft"
  "exception-reporting":
    userId: "fb7193ae-67e0-479a-ae72-e9dad3b0861b"
  "find-and-replace":
    autocompleteSearches: true
    closeFindPanelAfterSearch: true
    projectSearchResultsPaneSplitDirection: "down"
    scrollToResultOnLiveSearch: true
  "fuzzy-finder":
    scoringSystem: "fast"
    useRipGrep: true
  "highlight-selected":
    highlightBackground: true
  "line-ending-selector":
    defaultLineEnding: "LF"
  "markdown-preview":
    breakOnSingleNewline: true
    useGitHubStyle: true
  "markdown-preview-enhanced":
    enableExtendedTableSyntax: true
    previewTheme: "one-light.css"
  "one-dark-ui":
    stickyHeaders: true
    tabSizing: "Minimum"
  "platformio-ide-terminal":
    core:
      shell: "C:\\Windows\\System32\\cmd.exe"
      workingDirectory: "Home"
    style:
      theme: "one-dark"
  tabs:
    addNewTabsAtEnd: true
    enableVcsColoring: true
  "tree-view":
    hideIgnoredNames: true
    hideVcsIgnoredFiles: true
  welcome:
    showOnStartup: false
  "wrap-guide": {}
".c.source":
  editor:
    autoIndent: false
    autoIndentOnPaste: false



```

## 用户样式设置:
styles.less

```less

// style the background color of the tree view
.tree-view {
    //background-color: whitesmoke;
    //background-color: RGB(208, 255, 255);//目录树背景色
}

// style the background and foreground colors on the atom-text-editor-element itself
atom-text-editor {
    // color: white;//前景色(普通字体颜色)
    // background-color: RGB(208, 255, 255);//编辑框背景色
}

// style UI elements inside atom-text-editor
atom-text-editor .cursor {
     //border-color: blue;//光标颜色
}

//注释风格
atom-text-editor .syntax--comment {
    font-style: normal; //将注释的斜体修改为正常体
    //font-size: 12px; //注释字号
    //color:  #2C713C; //注释颜色
}

```

## atom常用插件
#### auto-encoding
    自动转换文件编码
    
#### highlight-selected
    选中高亮
    
#### language-batch
    语言支持-batch
    
#### language-cmake
    语言支持-cmake
    
#### language-cpp14
    语言支持c++
    
#### language-thrift
    语言支持-thrift
    
#### markdown-preview-enhanced
    应该是ATOM最好、功能最强的Markdown插件
    如果需要使用plantuml,需要额外安装:graphviz:
    http://www.graphviz.org/download/
    
    如果需要使用plantuml,需要额外安装java:
    https://www.java.com/zh_CN/
    https://sourceforge.net/projects/plantuml/files/plantuml.jar/download
    
    plantuml语法教程:
    http://plantuml.com/class-diagram
    
    语言支持-Markdown语法高亮:
    language-gfm-enhanced
    language-dot
    language-mermaid
    language-plantuml
    language-markdown
    
    如果需要导出pdf,需要安装 princexml
    否则会报错:"princexml" is required to be installed.
    https://www.princexml.com/download/
    安装后需要设置环境变量
    选择右键我的电脑->属性->高级系统设置->环境变量->系统变量->Path->编辑
    把安装路径 C:\Program Files (x86)\Prince\engine\bin 这一路径添加到新建Path环境变量即可。


#### multiline-tab
    多行标签栏
    
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
        
#### simlified-chinese-menu
    中文汉化插件
    
