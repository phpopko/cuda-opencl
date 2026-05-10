#include "ocl.h"
#include <stdio.h>

#ifdef _WIN32
#define LOAD(fn) do { \
    ocl->fn = (PFN_cl##fn)(void *)GetProcAddress((HMODULE)ocl->handle, "cl" #fn); \
    if (!ocl->fn) { fprintf(stderr, "Failed to load: cl%s\n", #fn); return -1; } \
} while(0)
#else
#define LOAD(fn) do { \
    ocl->fn = (PFN_cl##fn)dlsym(ocl->handle, "cl" #fn); \
    if (!ocl->fn) { fprintf(stderr, "Failed to load: cl%s\n", #fn); return -1; } \
} while(0)
#endif

cl_int ocl_init(OCL *ocl) {
#ifdef _WIN32
    ocl->handle = LoadLibraryA("OpenCL.dll");
#else
    ocl->handle = dlopen("libOpenCL.so", RTLD_LAZY);
#endif
    if (!ocl->handle) {
        fprintf(stderr, "Failed to load OpenCL library\n");
        return -1;
    }

    LOAD(GetPlatformIDs);
    LOAD(GetDeviceIDs);
    LOAD(CreateContext);
    LOAD(CreateCommandQueue);
    LOAD(CreateProgramWithSource);
    LOAD(BuildProgram);
    LOAD(CreateKernel);
    LOAD(CreateBuffer);
    LOAD(SetKernelArg);
    LOAD(EnqueueNDRangeKernel);
    LOAD(EnqueueReadBuffer);
    LOAD(Finish);
    LOAD(Flush);
    LOAD(ReleaseKernel);
    LOAD(ReleaseProgram);
    LOAD(ReleaseMemObject);
    LOAD(ReleaseCommandQueue);
    LOAD(ReleaseContext);
    LOAD(GetPlatformInfo);
    LOAD(GetDeviceInfo);
    LOAD(GetProgramBuildInfo);
    LOAD(GetKernelWorkGroupInfo);

    return CL_SUCCESS;
}

void ocl_close(OCL *ocl) {
    if (ocl->handle) {
#ifdef _WIN32
        FreeLibrary((HMODULE)ocl->handle);
#else
        dlclose(ocl->handle);
#endif
        ocl->handle = NULL;
    }
}

const char *ocl_error_str(cl_int err) {
    switch (err) {
        case CL_SUCCESS:                     return "CL_SUCCESS";
        case CL_DEVICE_NOT_FOUND:            return "CL_DEVICE_NOT_FOUND";
        case CL_INVALID_VALUE:               return "CL_INVALID_VALUE";
        case CL_INVALID_PLATFORM:            return "CL_INVALID_PLATFORM";
        case CL_INVALID_DEVICE_TYPE:         return "CL_INVALID_DEVICE_TYPE";
        case CL_INVALID_CONTEXT:             return "CL_INVALID_CONTEXT";
        case CL_INVALID_COMMAND_QUEUE:       return "CL_INVALID_COMMAND_QUEUE";
        case CL_INVALID_BUFFER_SIZE:         return "CL_INVALID_BUFFER_SIZE";
        case CL_INVALID_PROGRAM:             return "CL_INVALID_PROGRAM";
        case CL_INVALID_PROGRAM_EXECUTABLE:  return "CL_INVALID_PROGRAM_EXECUTABLE";
        case CL_INVALID_KERNEL:              return "CL_INVALID_KERNEL";
        case CL_INVALID_KERNEL_ARGS:         return "CL_INVALID_KERNEL_ARGS";
        case CL_INVALID_WORK_DIMENSION:      return "CL_INVALID_WORK_DIMENSION";
        case CL_INVALID_WORK_GROUP_SIZE:     return "CL_INVALID_WORK_GROUP_SIZE";
        case CL_MEM_OBJECT_ALLOCATION_FAILURE: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
        case CL_OUT_OF_RESOURCES:            return "CL_OUT_OF_RESOURCES";
        case CL_OUT_OF_HOST_MEMORY:          return "CL_OUT_OF_HOST_MEMORY";
        case CL_BUILD_PROGRAM_FAILURE:       return "CL_BUILD_PROGRAM_FAILURE";
        default: return "UNKNOWN";
    }
}
