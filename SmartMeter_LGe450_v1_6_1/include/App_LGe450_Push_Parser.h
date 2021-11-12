//https://stackoverflow.com/questions/43537587/c-function-calling-c-member-function-where-the-c-code-is-compiled-with-a-c-c

#ifndef APP_LGe450_PUSH_PARSER_H_
#define APP_LGe450_PUSH_PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif

//Data structure
struct Smart_Meter_data_t {
    uint16_t Strom_L1;
    uint16_t Strom_L2;
    uint16_t Strom_L3;
    uint32_t Wirkleistungsbezug;
    uint32_t Wirkenergiebezug_Tarif_1;
    uint32_t Wirkenergiebezug_Tarif_2;
};

//Number of struct elements for new_data_bitmask = n_data / 8 -> round up to byte
extern uint8_t new_data_bitmask[1];  

//Data
extern const struct Smart_Meter_data_t Smart_Meter_data_init;
extern struct Smart_Meter_data_t Smart_Meter_data;

//Parser DOne Semaphore
extern struct k_sem parser_done_sem;

void* App_LGe450_Push_Parser_create();
void App_LGe450_Push_Parser_release(void* app_LGe450_Push_Parser);
void App_LGe450_Push_Parser_parse(void* app_LGe450_Push_Parser, const void* pSource, unsigned long count);

#if defined(__cplusplus)
}
#endif

#endif //APP_LGe450_PUSH_PARSER_H_
