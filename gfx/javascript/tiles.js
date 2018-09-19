class Tile {
	constructor(opts) {
		this.x					= opts.x;
		this.y					= opts.y;
		this.inventory = {
			eggs: 0,
			food: 0,
			stone1: 0,
			stone2: 0,
			stone3: 0,
			stone4: 0,
			stone5: 0
		};
		this.contentSprites		= [];
	}

	get center() {
		return { x: this.x * TILE_SIZE, y: this.y * TILE_SIZE };
	}

	addContent(type, amt) {
		this.inventory[type] += amt;
		for (var i = 0; i < amt; i++) {
			this.addContentSprite(type);
		}
	}

	addContentSprite(type) {
		const sp = new BABYLON.Sprite(type, game.getContentSpriteManagerFor(type));
		sp.position.x = this.y * (TILE_SIZE + Math.random() * 2 - 1);
		sp.position.y = 5;
		sp.position.z = this.x * (TILE_SIZE + Math.random() * 2 - 1);
		sp.size = 3;
		this.contentSprites.push(sp);
	}
}
