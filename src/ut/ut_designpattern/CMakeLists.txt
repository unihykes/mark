PROJECT(ut_designpattern)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(VERSION 2.8)



INCLUDE($ENV{MONK_MAKE}/begin.cmake)

SET(TARGET_TYPE RUNTIME)
SET(TARGET_NAME ut_designpattern)
SET(AUTO_RUN OFF)

#“¿¿µø‚
SET(NEED_GTEST TRUE)

# ±‡“Îƒø¬º
ADD_SOURCE_DIRS(./AbstractFactoryPattern;
				./AdapterPattern;
				./BridgePattern;
				./BuilderPattern;
				./ChainOfResponsibilityPattern;
				./CommandPattern;
				./CompositePattern;
				./DecoratorPattern;
				./FacadePattern;
				./FactoryPattern;
				./FlyweightPattern;
				./InterpreterPattern;
				./IteratorPattern;
				./MediatorPattern;
				./MementoPattern;
				./ObserverPattern;
				./PrototypePattern;
				./ProxyPattern;
				./SingletonPattern;
				./StatePattern;
				./StrategyPattern;
				./TemplatePattern;
				./VisitorPattern;)

INCLUDE($ENV{MONK_MAKE}/end.cmake)



