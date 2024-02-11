/*
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/ioctl.h>
#include <linux/drm.h>

int main() {
    int fd = open("/dev/dri/card0", O_RDWR);
    if (fd < 0) {
        // Ошибка открытия устройства
        return -1;
    }

    drmVBlank vbl;
    vbl.request.type = DRM_VBLANK_RELATIVE | DRM_VBLANK_EVENT;
    vbl.request.sequence = 1;

    int ret = ioctl(fd, DRM_IOCTL_WAIT_VBLANK, &vbl);
    if (ret == 0) {
        // Событие VSYNC произошло
        // Ваш код обработки события
    }

    close(fd);
    
    return 0;
}
*/