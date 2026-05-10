#ifndef OCL_H
#define OCL_H

#include <stdint.h>
#include <stddef.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

typedef int32_t  cl_int;
typedef uint32_t cl_uint;
typedef uint64_t cl_ulong;
typedef cl_uint  cl_bool;
typedef cl_ulong cl_bitfield;
typedef cl_bitfield cl_device_type;
typedef cl_uint  cl_platform_info;
typedef cl_uint  cl_device_info;
typedef cl_uint  cl_context_info;
typedef cl_uint  cl_command_queue_info;
typedef cl_bitfield cl_mem_flags;
typedef cl_bitfield cl_command_queue_properties;
typedef cl_bitfield cl_queue_properties;
typedef cl_uint  cl_program_build_info;
typedef cl_uint  cl_kernel_work_group_info;
typedef cl_ulong cl_device_partition_property;
typedef intptr_t cl_context_properties;

typedef struct _cl_platform_id *   cl_platform_id;
typedef struct _cl_device_id *     cl_device_id;
typedef struct _cl_context *       cl_context;
typedef struct _cl_command_queue * cl_command_queue;
typedef struct _cl_program *       cl_program;
typedef struct _cl_kernel *        cl_kernel;
typedef struct _cl_mem *           cl_mem;
typedef struct _cl_event *         cl_event;
typedef struct _cl_sampler *       cl_sampler;

#define CL_SUCCESS                         0
#define CL_DEVICE_NOT_FOUND               -1
#define CL_INVALID_VALUE                  -30
#define CL_INVALID_PLATFORM               -32
#define CL_INVALID_DEVICE_TYPE            -31
#define CL_INVALID_CONTEXT                -34
#define CL_INVALID_QUEUE_PROPERTIES       -35
#define CL_INVALID_COMMAND_QUEUE          -36
#define CL_INVALID_HOST_PTR               -37
#define CL_INVALID_MEM_OBJECT             -38
#define CL_INVALID_BUFFER_SIZE            -61
#define CL_INVALID_PROGRAM                -44
#define CL_INVALID_PROGRAM_EXECUTABLE     -45
#define CL_INVALID_KERNEL                 -46
#define CL_INVALID_KERNEL_ARGS            -52
#define CL_INVALID_WORK_DIMENSION         -53
#define CL_INVALID_WORK_GROUP_SIZE        -54
#define CL_INVALID_WORK_ITEM_SIZE         -55
#define CL_INVALID_GLOBAL_OFFSET          -56
#define CL_INVALID_EVENT_WAIT_LIST        -57
#define CL_MEM_OBJECT_ALLOCATION_FAILURE  -4
#define CL_OUT_OF_RESOURCES               -5
#define CL_OUT_OF_HOST_MEMORY             -6
#define CL_BUILD_PROGRAM_FAILURE          -11
#define CL_MAP_FAILURE                    -12

#define CL_FALSE    0
#define CL_TRUE     1
#define CL_DEVICE_TYPE_GPU        (1 << 2)
#define CL_DEVICE_TYPE_CPU        (1 << 1)
#define CL_DEVICE_TYPE_ALL        0xFFFFFFFF

#define CL_DEVICE_NAME            0x102B
#define CL_DEVICE_VENDOR          0x102C
#define CL_DRIVER_VERSION         0x102D
#define CL_DEVICE_MAX_COMPUTE_UNITS  0x1002
#define CL_DEVICE_MAX_WORK_GROUP_SIZE 0x1004
#define CL_DEVICE_GLOBAL_MEM_SIZE    0x101F

#define CL_MEM_READ_WRITE     (1 << 0)
#define CL_MEM_READ_ONLY      (1 << 2)
#define CL_MEM_WRITE_ONLY     (1 << 3)
#define CL_MEM_COPY_HOST_PTR  (1 << 5)
#define CL_MEM_ALLOC_HOST_PTR (1 << 7)

#define CL_QUEUE_PROFILING_ENABLE (1 << 1)
#define CL_PROGRAM_BUILD_LOG      0x1183

typedef cl_int  (*PFN_clGetPlatformIDs)(cl_uint, cl_platform_id *, cl_uint *);
typedef cl_int  (*PFN_clGetDeviceIDs)(cl_platform_id, cl_device_type, cl_uint, cl_device_id *, cl_uint *);
typedef cl_context (*PFN_clCreateContext)(const cl_context_properties *, cl_uint, const cl_device_id *, void (*)(const char *, const void *, size_t, void *), void *, cl_int *);
typedef cl_command_queue (*PFN_clCreateCommandQueueWithProperties)(cl_context, cl_device_id, const cl_queue_properties *, cl_int *);
typedef cl_command_queue (*PFN_clCreateCommandQueue)(cl_context, cl_device_id, cl_command_queue_properties, cl_int *);
typedef cl_program (*PFN_clCreateProgramWithSource)(cl_context, cl_uint, const char **, const size_t *, cl_int *);
typedef cl_int  (*PFN_clBuildProgram)(cl_program, cl_uint, const cl_device_id *, const char *, void (*)(cl_program, void *), void *);
typedef cl_kernel (*PFN_clCreateKernel)(cl_program, const char *, cl_int *);
typedef cl_mem  (*PFN_clCreateBuffer)(cl_context, cl_mem_flags, size_t, void *, cl_int *);
typedef cl_int  (*PFN_clSetKernelArg)(cl_kernel, cl_uint, size_t, const void *);
typedef cl_int  (*PFN_clEnqueueNDRangeKernel)(cl_command_queue, cl_kernel, cl_uint, const size_t *, const size_t *, const size_t *, cl_uint, const cl_event *, cl_event *);
typedef cl_int  (*PFN_clEnqueueReadBuffer)(cl_command_queue, cl_mem, cl_bool, size_t, size_t, void *, cl_uint, const cl_event *, cl_event *);
typedef cl_int  (*PFN_clFinish)(cl_command_queue);
typedef cl_int  (*PFN_clFlush)(cl_command_queue);
typedef cl_int  (*PFN_clReleaseKernel)(cl_kernel);
typedef cl_int  (*PFN_clReleaseProgram)(cl_program);
typedef cl_int  (*PFN_clReleaseMemObject)(cl_mem);
typedef cl_int  (*PFN_clReleaseCommandQueue)(cl_command_queue);
typedef cl_int  (*PFN_clReleaseContext)(cl_context);
typedef cl_int  (*PFN_clGetPlatformInfo)(cl_platform_id, cl_platform_info, size_t, void *, size_t *);
typedef cl_int  (*PFN_clGetDeviceInfo)(cl_device_id, cl_device_info, size_t, void *, size_t *);
typedef cl_int  (*PFN_clGetProgramBuildInfo)(cl_program, cl_device_id, cl_program_build_info, size_t, void *, size_t *);
typedef cl_int  (*PFN_clGetKernelWorkGroupInfo)(cl_kernel, cl_device_id, cl_kernel_work_group_info, size_t, void *, size_t *);

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void *handle;
    PFN_clGetPlatformIDs         GetPlatformIDs;
    PFN_clGetDeviceIDs           GetDeviceIDs;
    PFN_clCreateContext          CreateContext;
    PFN_clCreateCommandQueue     CreateCommandQueue;
    PFN_clCreateProgramWithSource CreateProgramWithSource;
    PFN_clBuildProgram           BuildProgram;
    PFN_clCreateKernel           CreateKernel;
    PFN_clCreateBuffer           CreateBuffer;
    PFN_clSetKernelArg           SetKernelArg;
    PFN_clEnqueueNDRangeKernel   EnqueueNDRangeKernel;
    PFN_clEnqueueReadBuffer      EnqueueReadBuffer;
    PFN_clFinish                 Finish;
    PFN_clFlush                  Flush;
    PFN_clReleaseKernel          ReleaseKernel;
    PFN_clReleaseProgram         ReleaseProgram;
    PFN_clReleaseMemObject       ReleaseMemObject;
    PFN_clReleaseCommandQueue    ReleaseCommandQueue;
    PFN_clReleaseContext         ReleaseContext;
    PFN_clGetPlatformInfo        GetPlatformInfo;
    PFN_clGetDeviceInfo          GetDeviceInfo;
    PFN_clGetProgramBuildInfo    GetProgramBuildInfo;
    PFN_clGetKernelWorkGroupInfo GetKernelWorkGroupInfo;
} OCL;

cl_int ocl_init(OCL *ocl);
void   ocl_close(OCL *ocl);
const char *ocl_error_str(cl_int err);

#ifdef __cplusplus
}
#endif

#endif
