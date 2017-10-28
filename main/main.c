#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "esp_partition.h"


void app_main(void)
{
    nvs_flash_init();

    const esp_partition_t* part;
	spi_flash_mmap_handle_t handle;
    void* data;
	esp_err_t err;

	part = esp_partition_find_first(0x40, 1, NULL);
	if (part == 0)
	{
		printf("esp_partition_find_first failed.\n");
		abort();
	}

    printf("partition: type=%d, subtype=%d, address=0x%x, size=0x%x, label='%s', encrypted=%d\n",
        part->type, part->subtype, part->address, part->size, part->label, part->encrypted);

	printf("pre mmap heap=0x%x\n", esp_get_free_heap_size());

	err = esp_partition_mmap(part, 0, part->size, SPI_FLASH_MMAP_DATA, (const void**)&data, &handle);
	if (err!=ESP_OK)
	{
		printf("esp_partition_mmap failed. (%d)\n", err);
		abort();
	}

	printf("post mmap heap=0x%x\n", esp_get_free_heap_size());

	printf("mmap=%p\n", data);

    while (true)
    {
        vTaskDelay(300 / portTICK_PERIOD_MS);
    }
}
