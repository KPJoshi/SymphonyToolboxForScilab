mode(-1)
lines(0)

//Symphony toolbox help builder
//By Keyur Joshi, Sai Kiran and Iswarya

TOOLBOX_TITLE = "symphonytools"

tbx_build_help(TOOLBOX_TITLE,get_absolute_file_path("builder_help.sce"));
add_help_chapter(TOOLBOX_TITLE,get_absolute_file_path("builder_help.sce"));

clear TOOLBOX_TITLE;
