/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "mycar.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId gimbaltaskHandle;
osThreadId chassistaskHandle;
osThreadId decodeTaskHandle;
osThreadId sendTaskHandle;
osThreadId modeTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void Startgimbaltask(void const * argument);
void Startchassistask(void const * argument);
void StartdecodeTask(void const * argument);
void StartsendTask(void const * argument);
void StartmodeTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
{
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
  /* place for user code */
}
/* USER CODE END GET_TIMER_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of gimbaltask */
  osThreadDef(gimbaltask, Startgimbaltask, osPriorityHigh, 0, 256);
  gimbaltaskHandle = osThreadCreate(osThread(gimbaltask), NULL);

  /* definition and creation of chassistask */
  osThreadDef(chassistask, Startchassistask, osPriorityHigh, 0, 256);
  chassistaskHandle = osThreadCreate(osThread(chassistask), NULL);

  /* definition and creation of decodeTask */
  osThreadDef(decodeTask, StartdecodeTask, osPriorityRealtime, 0, 256);
  decodeTaskHandle = osThreadCreate(osThread(decodeTask), NULL);

  /* definition and creation of sendTask */
  osThreadDef(sendTask, StartsendTask, osPriorityNormal, 0, 128);
  sendTaskHandle = osThreadCreate(osThread(sendTask), NULL);

  /* definition and creation of modeTask */
  osThreadDef(modeTask, StartmodeTask, osPriorityAboveNormal, 0, 256);
  modeTaskHandle = osThreadCreate(osThread(modeTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    HAL_GPIO_TogglePin(GPIOH,GPIO_PIN_11);
    osDelay(100);

  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Startgimbaltask */
/**
* @brief Function implementing the gimbaltask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Startgimbaltask */
void Startgimbaltask(void const * argument)
{
  /* USER CODE BEGIN Startgimbaltask */
  Gimbal_Init();
  /* Infinite loop */
  for(;;)
  {
    Gimbal_Task();
    osDelay(1);
  }
  /* USER CODE END Startgimbaltask */
}

/* USER CODE BEGIN Header_Startchassistask */
/**
* @brief Function implementing the chassistask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Startchassistask */
void Startchassistask(void const * argument)
{
  /* USER CODE BEGIN Startchassistask */
  Chassis_Init();
  /* Infinite loop */
  for(;;)
  {
    Chassis_Task();
    osDelay(1);
  }
  /* USER CODE END Startchassistask */
}

/* USER CODE BEGIN Header_StartdecodeTask */
/**
* @brief Function implementing the decodeTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartdecodeTask */
void StartdecodeTask(void const * argument)
{
  /* USER CODE BEGIN StartdecodeTask */
  /* Infinite loop */
  for(;;)
  {
    Decode_Task();
    osDelay(1);
  }
  /* USER CODE END StartdecodeTask */
}

/* USER CODE BEGIN Header_StartsendTask */
/**
* @brief Function implementing the sendTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartsendTask */
void StartsendTask(void const * argument)
{
  /* USER CODE BEGIN StartsendTask */
  /* Infinite loop */
  for(;;)
  {
    Send_Task();
    osDelay(1);
  }
  /* USER CODE END StartsendTask */
}

/* USER CODE BEGIN Header_StartmodeTask */
/**
* @brief Function implementing the modeTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartmodeTask */
void StartmodeTask(void const * argument)
{
  /* USER CODE BEGIN StartmodeTask */
  /* Infinite loop */
  for(;;)
  {
    Mode_Task();
    osDelay(1);
  }
  /* USER CODE END StartmodeTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
