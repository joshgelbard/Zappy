class Gui{
	constructor() {
		this.advTex = BABYLON.GUI.AdvancedDynamicTexture.CreateFullscreenUI("myUI");
		this.leaderboardFontSize = 18;
		this.leaderboard = {
			panel:		undefined,
			text:		[],
		};
	}

	updateLeaderboardText() {
		var cmp = function(a, b) {
			if (a.highestLevelOnTeam !== b.highestLevelOnTeam) {
				return (b.highestLevelOnTeam - a.highestLevelOnTeam);
			}
			return (b.playersAtHighestLevel - a.playersAtHighestLevel);
		};

		var oldInfo;
		if (this.currentTeamInfo) {
			oldInfo = this.currentTeamInfo.slice(0);
		}
		this.currentTeamInfo = _.cloneDeep(stats.teams);
		this.currentTeamInfo.sort(cmp);
		if (oldInfo && _.isEqual(oldInfo, this.currentTeamInfo)) {
			return ;
		}

		for (var i = 0; i < this.leaderboard.text.length; i++) {
			this.leaderboard.text[i].dispose();
		}

		for (var i = 0; i < this.currentTeamInfo.length; i++) {
			this.leaderboard.text[i] = this._createLeaderboardText(
				this.leaderboard.panel,
				`${i + 1}. ${this.currentTeamInfo[i].teamName} ${this.currentTeamInfo[i].playersAtHighestLevel} at level ${this.currentTeamInfo[i].highestLevelOnTeam} (out of ${this.currentTeamInfo[i].playersOnTeam})`,
				i
			);
			this.advTex.addControl(this.leaderboard.text[i]);
		}
	}

	displayPlayerDetail() {
		this.playerDetail = new PlayerDetail();
		this.advTex.addControl(this.playerDetail);
		this.playerDetail.horizontalAlignment =
			BABYLON.GUI.Control.HORIZONTAL_ALIGNMENT_RIGHT;
		this.playerDetail.verticalAlignment =
			BABYLON.GUI.Control.VERTICAL_ALIGNMENT_BOTTOM;
	}

	displayLeaderboard() {
		this.leaderboard.panel = this._createPanel({height:200, width:400}, {left:20, top:20}, "top", "left");
		this.leaderboard.panel.alpha = 0.2;
		this.leaderboard.panel.onPointerEnterObservable.add(() => {
			this.leaderboard.panel.alpha = 0.8;
		});
		this.leaderboard.panel.onPointerOutObservable.add(() => {
			this.leaderboard.panel.alpha = 0.2;
		});
		this.advTex.addControl(this.leaderboard.panel);
		this.updateLeaderboardText();
	}
	
	_createPanel(size, offset, vert, hor, color) {
		var rectangle = new BABYLON.GUI.Rectangle("rect");
		
		if (color && color.backgroundColor) {
			rectangle.background = color.backgroundColor;
		} else {
			rectangle.background = "black";
		}

		if (color && color.edgeColor) {
			rectangle.color = color.edgeColor;
		} else {
			rectangle.color = "grey";
		}
		rectangle.alpha = 1;
		rectangle.width = size.width + "px";
		rectangle.height = size.height + "px";
		rectangle.horizontalAlignment = {left:		BABYLON.GUI.Control.HORIZONTAL_ALIGNMENT_LEFT,
										 center:	BABYLON.GUI.Control.HORIZONTAL_ALIGNMENT_CENTER,
										 right:		BABYLON.GUI.Control.HORIZONTAL_ALIGNMENT_RIGHT	}[hor];
		rectangle.verticalAlignment = {	 top:		BABYLON.GUI.Control.VERTICAL_ALIGNMENT_TOP,
										 center:	BABYLON.GUI.Control.VERTICAL_ALIGNMENT_CENTER,
										 bottom:	BABYLON.GUI.Control.VERTICAL_ALIGNMENT_BOTTOM	}[vert];
		rectangle.left = offset.left;
		rectangle.top = offset.top;

		rectangle.__left__ = offset.left;
		rectangle.__top__ = offset.top;

		return (rectangle);
	}

	_createLeaderboardText(panel, text, idx) {

		const leftMargin = 20;
		const topMargin = 40;
		var text = new BABYLON.GUI.TextBlock("text", text);
		text.color = "white";
		text.fontSize = this.leaderboardFontSize;
		text.isHitTestVisible = false;

		text.textHorizontalAlignment = BABYLON.GUI.Control.HORIZONTAL_ALIGNMENT_LEFT;
		text.textVerticalAlignment = BABYLON.GUI.Control.VERTICAL_ALIGNMENT_TOP;

		text.left = panel.__left__ + leftMargin;
		text.top = panel.__top__ + topMargin + (idx * (this.leaderboardFontSize + 4));

		return (text);
	}
}
