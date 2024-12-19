install(
    TARGETS ebm_exe
    RUNTIME COMPONENT ebm_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
