//https://stackoverflow.com/questions/43537587/c-function-calling-c-member-function-where-the-c-code-is-compiled-with-a-c-c

#ifdef __cplusplus
extern "C" {
#endif

void* App_LGe450_Push_Parser_create();
void App_LGe450_Push_Parser_release(void* app_LGe450_Push_Parser);
void App_LGe450_Push_Parser_parse(void* app_LGe450_Push_Parser, const void* pSource, unsigned long count);

#if defined(__cplusplus)
}
#endif
