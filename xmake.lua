add_rules("mode.debug", "mode.release")

add_requires("libhv 1.3.2", {configs={http_server=false}})
add_requires("nlohmann_json v3.11.3")
add_requires("spdlog v1.13.0")

target("bot")
    add_files("src/**.cpp")
    add_headerfiles("src/(**.h)")
    add_includedirs("src")
    add_packages(
        "libhv",
        "nlohmann_json",
        "spdlog"
    )
    set_exceptions("cxx")
    set_kind("binary")
    set_languages("cxx20")
