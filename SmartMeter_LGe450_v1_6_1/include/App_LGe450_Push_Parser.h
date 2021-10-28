//https://stackoverflow.com/questions/43537587/c-function-calling-c-member-function-where-the-c-code-is-compiled-with-a-c-c

#ifndef APP_LGe450_PUSH_PARSER_H_
#define APP_LGe450_PUSH_PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif

void* App_LGe450_Push_Parser_create();
void App_LGe450_Push_Parser_release(void* app_LGe450_Push_Parser);
void App_LGe450_Push_Parser_parse(void* app_LGe450_Push_Parser, const void* pSource, unsigned long count);

#if defined(__cplusplus)
}
#endif

#endif //APP_LGe450_PUSH_PARSER_H_
