# Maintainer: Kirill Vilkov <wide.wrd@gmail.com> 
pkgname=qaib
pkgver=0.1
pkgrel=1
pkgdesc="Neuroevolution game"
arch=('i686' 'x86_64')
license=('unknown')
depends=('sfml' 'box2d' 'glm')
makedepends=('cmake')
md5sums=('SKIP')
source=("$pkgname-$pkgver.tar.gz")

build() {
	cd "$pkgname-$pkgver"
    cmake .
    make 
}

package() {
	cd "$pkgname-$pkgver"
	make DESTDIR="$pkgdir/" install
}
