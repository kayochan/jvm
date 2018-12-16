#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "jvm.h"
#include "native/registry.h"
#include "../test/test.h"
#include "util/bigendian.h"

static char main_class[FILENAME_MAX] = { 0 };

/*
 * -bcp path: Bootstrap Class Path, JavaHome路径, 对应 jre/lib 目录。
 */
static bool parse_args(int argc, char* argv[])
{
    // 可执行程序的名字为 argv[0]，跳过。
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            const char *name = argv[i];
            if (strcmp(name, "-bcp") == 0) {
                if (++i >= argc) {
                    printvm("缺少参数：%s\n", name);
                    return false;
                }
                const char *value = argv[i];
                strcpy(bootstrap_classpath, value);
            } else {
                printvm("不认识的参数：%s\n", name);
                return false;
            }
        } else {
            strcpy(main_class, argv[i]);
        }
    }

    if (main_class[0] == 0) {  // empty
        printvm("无main class\n");
        return false;
    }

    return true;
}

int main(int argc, char* argv[])
{
    if (!parse_args(argc, argv)) {
        jvm_abort("error\n"); // todo
        return -1;
    }

    // 命令行参数没有设置 bootstrap_classpath 的值，那么使用 JAVA_HOME 环境变量
    if (bootstrap_classpath[0] == 0) { // empty
        char *java_home = getenv("JAVA_HOME"); // JAVA_HOME 是 JDK 的目录
        if (java_home == NULL) {
            // todo error
            printvm("no java home");
            return -1;
        }
        strcpy(bootstrap_classpath, java_home);
        strcat(bootstrap_classpath, "/jre/lib");
    }

    if (extension_classpath[0] == 0) {  // empty
        strcpy(extension_classpath, bootstrap_classpath);
        strcat(extension_classpath, "/ext");  // todo JDK9+ 的目录结构有变动！！！！！！！
    }

//    printvm("bootstrap_classpath: %s\n", bootstrap_classpath);
//    printvm("extension_classpath: %s\n", extension_classpath);
//    printvm("user_classpath: %s\n", user_classpath);

    // todo 测试 JAVA_HOME 是不是  java8  版本
//    jvm_abort("just support java8.\n");

    register_all_native_methods();
//    print_registered_native_methods();

    void test();
    test();

    return 0;
}

void test()
{
//    test_vector();
//    test_hashmap();

    // 未分类
     start_jvm("HelloWorld");
//    start_jvm("ObjectInitTest");

    // lambda
//    start_jvm("lambda/LambdaTest");

    // invoke
//    start_jvm("invoke/InvokeFuncTest1");

    // array
//    start_jvm("array/BubbleSort"); // pass
  //  start_jvm("array/ArrayTest"); // pass

    // string
    //start_jvm("string/StringTest");
//    start_jvm("io/github/jiayanggo/string/Mutf8Test");

//    start_jvm("TimeZoneTest");
//    start_jvm("ObjectTest");
//    start_jvm("string/StringTest");

    // wrapper
//    start_jvm("wrapper/IntegerTest");
//    start_jvm("wrapper/FloatTest");

    // exception
//    start_jvm("exception/CatchTest");
//    start_jvm("exception/UncaughtTest");

//    start_jvm("ObjectInitTest");


//    start_jvm("io/github/jiayanggo/string/StringOut");
//    start_jvm("io/github/jiayanggo/ObjectTest");
//    start_jvm("io/github/jiayanggo/field/FieldsTest");

//    start_jvm("io/github/jiayanggo/exception/CatchTest");
//    start_jvm("io/github/jiayanggo/exception/UncaughtTest");

//    start_jvm("io/github/jiayanggo/reflection/GetClassTest");
//    start_jvm("io/github/jiayanggo/reflection/FieldTest");

//    start_jvm("io/github/jiayanggo/nio/ByteBufferTest");  // todo 没有实现的native方法。
}