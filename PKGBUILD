# Maintainer: Maxr1998 <max.rumpf1998@gmail.com>
pkgname=simple-shutdown-dialog
pkgver=1.8d62d57
pkgrel=1
pkgdesc="A simple dialog to shutdown, reboot, suspend or logout, built with GTK"
arch=('x86_64' 'i686')
url="https://github.com/git-fal7/SimpleShutdownDialog"
license=('GPL')
depends=('gtk3')
source=("$pkgname::git+$url.git")
sha256sums=("SKIP")

pkgver() {
    cd "$pkgname"
    printf "%s.%s" "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)"
}

build() {
    cd "$pkgname"
    make
}

package() {
    cd "$pkgname"
    install -Dm755 shutdown-dialog "$pkgdir"/usr/bin/shutdown-dialog
    install -Dm755 shutdown-dialog.desktop "$pkgdir"/usr/share/applications/shutdown-dialog.desktop
}
