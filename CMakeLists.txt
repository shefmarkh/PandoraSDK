# Declare the package name:
atlas_subdir( PandoraSDK )

atlas_add_library ( PandoraSDKLib */*.h src/*/*.cc
  PUBLIC_HEADERS PandoraSDK
  SHARED)
